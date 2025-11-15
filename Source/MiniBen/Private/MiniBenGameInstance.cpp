// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <LevelStreamingUtils/Public/CustomWorldSubsystem.h>
#include <LevelStreamingUtils/Public/LevelStreamingFunctionsUtils.h>
#include "PlayerActions/Public/Saveable.h"
#include "GameFramework/Character.h"
#include "GameEventsBroker.h"


void UMiniBenGameInstance::Init()
{
    Super::Init();

    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMiniBenGameInstance::OnLevelChanged); //bind to level changed delegate
    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMiniBenGameInstance::PreLoadMapEvent);   //bind to level ABOUT to change delegate
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
}


/// <summary>
/// When leve changes, we record the new level name, we try to init a new world entry if it does not exist
/// We start the restore process from the loaded save file
/// </summary>
/// <param name="LoadedWorld"></param>
void UMiniBenGameInstance::OnLevelChanged_Implementation(UWorld* LoadedWorld)
{
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld()); //another safeguard to make sure the level name is saved correctly
    InitCurrentWorld();
    BeginLoadLevelProcess();
}

/// <summary>
/// I need this delegate to update my current level name so that all the saveable items in the new level
/// could reload their state based on the CurrentLevelName Key lookup
/// </summary>
/// <param name="temp">The long path level name that is about to load</param>
void UMiniBenGameInstance::PreLoadMapEvent_Implementation(const FString& temp)
{
    RecordCurrentProgress();
    FString LevelName = FPaths::GetBaseFilename(temp);
    CurrentLevelName = LevelName;
}

//I need to add newly encoutered level to the map of levels, if it is already there, just return
void UMiniBenGameInstance::InitCurrentWorld()
{
    if (!IsCurrentLevelGameLevel()) { return; }
    FWorldDataSave* WorldData = MainSaveData.AllLevels.Find(CurrentLevelName);

    if (!MainSaveData.AllLevels.Contains(CurrentLevelName))
    {
        MainSaveData.AllLevels.Add(CurrentLevelName, FWorldDataSave());
    }

    this->CurrentWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

}

void UMiniBenGameInstance::SaveSublevels()
{
	UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();

    MainSaveData.LastSavedLevel = *CurrentLevelName; // save the level 

    if (CustomWorldSubsystem)
    {
        if (CurrentWorldDataSave)
        {
            CurrentWorldDataSave->bHasLevelBeenInitialized = true;

            auto AllSublevels = CustomWorldSubsystem->GetAllSubLevels(GetWorld());
            FString SubLevelName;

            for (const auto& ele : AllSublevels)
            {
                SubLevelName = ULevelStreamingFunctionsUtils::ConvertLevelStreamingInstanceToString(ele);
                CurrentWorldDataSave->ListOfSublevels.Add(SubLevelName, ele->IsLevelVisible());
            }
        }
    }
}

void UMiniBenGameInstance::SavePlayer()
{
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        auto Character = PlayerController->GetCharacter();
        if (Character)
        {
            ISaveable::Execute_SaveAndRecordSelf(Character);
        }
    }
}


void UMiniBenGameInstance::AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem)
{

    //NEW WAY, BETTER WAY
    if (CurrentWorldDataSave)
    {
        bool isFound = CurrentWorldDataSave->MapOfLevelWorldItems.Contains(newItem.Guid);
        if (!isFound)
        {
            CurrentWorldDataSave->MapOfLevelWorldItems.Add(newItem.Guid, newItem);
        }
        else
        {
            CurrentWorldDataSave->MapOfLevelWorldItems[newItem.Guid] = newItem;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AddNewWorldAssetToSaveData CurrentLevelWorldDataSave was not found"));
    }
    
}

void UMiniBenGameInstance::AddNPCToSaveData(const FSaveableWorldNpcs& newNpc)
{
    if (CurrentWorldDataSave)
    {
        bool isFound = CurrentWorldDataSave->MapOfLevelSaveableNpcs.Contains(newNpc.Guid);
        if (!isFound)
        {
            CurrentWorldDataSave->MapOfLevelSaveableNpcs.Add(newNpc.Guid, newNpc);
        }
        else
        {
            CurrentWorldDataSave->MapOfLevelSaveableNpcs[newNpc.Guid] = newNpc;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AddNPCToSaveData CurrentLevelWorldDataSave was not found"));
    }
}

void UMiniBenGameInstance::AddEnemyToSaveData(const FSavealbeWorldEnemy& newEnemy)
{
    if (CurrentWorldDataSave)
    {
        bool isFound = CurrentWorldDataSave->MapOfLevelSaveableEnemies.Contains(newEnemy.Guid);
        if (!isFound)
        {
            CurrentWorldDataSave->MapOfLevelSaveableEnemies.Add(newEnemy.Guid, newEnemy);
        }
        else
        {
            CurrentWorldDataSave->MapOfLevelSaveableEnemies[newEnemy.Guid] = newEnemy;
        }
    }

    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AddEnemyToSaveData CurrentLevelWorldDataSave was not found"));
    }
}


void UMiniBenGameInstance::RestoreSublevels()
{
    // Get required references
    UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();
    FWorldDataSave* CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

    if (CurrentLevelWorldDataSave && CustomWorldSubsystem && CurrentLevelWorldDataSave->bHasLevelBeenInitialized)
    {
        TArray<ULevelStreaming*> AllSubLevels = CustomWorldSubsystem->GetAllSubLevels(GetWorld());
        SublevelQueue.Empty();  // Clear the queue

        // Populate the queue with sublevels to load/unload
        for (ULevelStreaming* ele : AllSubLevels)
        {
            FString SublevelName = ULevelStreamingFunctionsUtils::ConvertLevelStreamingInstanceToString(ele);
            bool* SublevelState = CurrentLevelWorldDataSave->ListOfSublevels.Find(SublevelName);

            if (SublevelState)
            {
                FQueuedSublevel QueuedSublevel;
                QueuedSublevel.Level = ele;
                QueuedSublevel.bShouldBeLoaded = *SublevelState;
                SublevelQueue.Enqueue(QueuedSublevel);  // Add to the queue
            }
        }

        // Start processing the queue
        ProcessNextSublevel();
    }
    else
    {
        //first time visit the level "bHasLevelBeenInitialized" is false
        NotifyPlayerToSelfRestore();
    }
}

const TMap<FGuid, FSaveableWorldItem> UMiniBenGameInstance::GetMapOfWorldItems() const
{
    if (!MainSaveData.AllLevels.Contains(this->CurrentLevelName))
    {
        UE_LOG(LogTemp, Warning, TEXT("GetMapOfWorldItems -> MainSaveData.AllLevels.Contains is empty"));
        return TMap<FGuid, FSaveableWorldItem>();
    }

    return MainSaveData.AllLevels[CurrentLevelName].MapOfLevelWorldItems;
}

const TMap<FGuid, FSaveableWorldNpcs> UMiniBenGameInstance::GetMapOfWorldNpcs() const
{
    if (!MainSaveData.AllLevels.Contains(this->CurrentLevelName))
    {
        UE_LOG(LogTemp, Warning, TEXT("GetMapOfWorldNpcs -> MainSaveData.AllLevels.Contains is empty"));
        return TMap<FGuid, FSaveableWorldNpcs>();
    }

    return MainSaveData.AllLevels[CurrentLevelName].MapOfLevelSaveableNpcs;
}

const TMap<FGuid, FSavealbeWorldEnemy> UMiniBenGameInstance::GetMapOfWorldEnemies() const
{
    if (!MainSaveData.AllLevels.Contains(this->CurrentLevelName))
    {
        UE_LOG(LogTemp, Warning, TEXT("GetMapOfWorldEnemies -> MainSaveData.AllLevels.Contains is empty"));
        return TMap<FGuid, FSavealbeWorldEnemy>();
    }

    return MainSaveData.AllLevels[CurrentLevelName].MapOfLevelSaveableEnemies;
}

void UMiniBenGameInstance::ProcessNextSublevel()
{
    // If the queue is empty, we're done
    if (SublevelQueue.IsEmpty())
    {
        NotifyPlayerToSelfRestore();
        return;
    }

    FQueuedSublevel NextSublevel;
    if (SublevelQueue.Dequeue(NextSublevel))
    {
        FLatentActionInfo LatentInfo;
        LatentInfo.ExecutionFunction = FName("FinishStreamLevelsFunc");
        LatentInfo.CallbackTarget = this;
        LatentInfo.Linkage = 0;
        LatentInfo.UUID = FMath::Rand();

        FString LevelPackageName = NextSublevel.Level->GetWorldAssetPackageName();

        // Fix: Directly construct a SoftObjectPtr from the path string
        TSoftObjectPtr<UWorld> LevelToLoad(LevelPackageName);

        if (NextSublevel.bShouldBeLoaded)
        {
            UGameplayStatics::LoadStreamLevelBySoftObjectPtr(
                GetWorld(),
                LevelToLoad,
                true,
                false,
                LatentInfo
            );
        }
        else
        {
            UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(
                GetWorld(),
                LevelToLoad,
                LatentInfo,
                false
            );
        }
    }
}

//Actors load and record themselves no need for manual load per actor
//void UMiniBenGameInstance::RestoreSaveableActorsForAllSublevels()
//{
//    UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();
//    
//
//    if (this->CurrentWorldDataSave && CustomWorldSubsystem && CurrentWorldDataSave->bHasLevelBeenInitialized)
//    {
//        TArray<ULevelStreaming*> AllSubLevels = CustomWorldSubsystem->GetAllSubLevels(GetWorld());
//      
//        // Populate the queue with sublevels to load/unload
//        for (ULevelStreaming* ele : AllSubLevels)
//        {
//            if (ele->IsLevelVisible())
//            {
//                for (AActor* actor : ele->GetLoadedLevel()->Actors)
//                {
//                    if (actor->Implements<USaveable>())
//                    {
//                        ISaveable::Execute_LoadAndRestoreSelf(actor);
//                    }
//                }
//            }
//        }
//    }
//}

void UMiniBenGameInstance::NotifyPlayerToSelfRestore()
{
    //All sublevels processed or never initialized
    //Let the player know that he can load and activate self
    GameEventsBroker::GetInst().BroadcastPlayerCanActivate();
}

void UMiniBenGameInstance::SetGlobalQuestData(const FGlobalQuestData& GlobalQuestData)
{
    this->MainSaveData.GlobalQuestData = GlobalQuestData;
}

void UMiniBenGameInstance::SavePlayerInventory(const TMap<FName, int32>& inventory)
{
    this->MainSaveData.PlayerInventory = inventory;
}

void UMiniBenGameInstance::SavePlayerTransform(const FPlayerTransformData& PlayerTransformData)
{
    this->CurrentWorldDataSave->PlayerTransformData = PlayerTransformData;
}

void UMiniBenGameInstance::SavePlayerAbilities(const TMap<FGameplayTag, bool>& PlayerAbilities)
{
    this->MainSaveData.PlayerAbilities = PlayerAbilities;
}

void UMiniBenGameInstance::SaveQuestsProgress(const TMap<FName, FActiveQuestProgress>& Progress)
{
    this->MainSaveData.ActiveQuestsProgress = Progress;
}

void UMiniBenGameInstance::SetCurrentWorldDataSave()
{
    this->CurrentWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);
}

void UMiniBenGameInstance::FinishStreamLevelsFunc()
{
    // Move to the next sublevel in the queue
    ProcessNextSublevel();
}

bool UMiniBenGameInstance::IsCurrentLevelGameLevel() const
{
    return this->CurrentLevelName != IntroLevelName;
}

