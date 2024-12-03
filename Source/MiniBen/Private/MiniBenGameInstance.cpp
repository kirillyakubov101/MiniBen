// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <LevelStreamingUtils/Public/CustomWorldSubsystem.h>
#include <LevelStreamingUtils/Public/LevelStreamingFunctionsUtils.h>
#include "PlayerActions/Public/Saveable.h"
#include "GameFramework/Character.h"


void UMiniBenGameInstance::Init()
{
    Super::Init();

    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMiniBenGameInstance::OnLevelChanged); //bind to level changed delegate
    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMiniBenGameInstance::RecordCurrentProgress);   //bind to level ABOUT to change delegate
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
}


/// <summary>
/// When leve changes, we record the new level name, we try to init a new world entry if it does not exist
/// We start the restore process from the loaded save file
/// </summary>
/// <param name="LoadedWorld"></param>
void UMiniBenGameInstance::OnLevelChanged_Implementation(UWorld* LoadedWorld)
{
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    InitCurrentWorld();
    BeginLoadLevelProcess();
}

//I need to add newly encoutered level to the map of levels, if it is already there, just return
void UMiniBenGameInstance::InitCurrentWorld()
{
    if (MainSaveData.AllLevels.Contains(CurrentLevelName)) { return; }

	MainSaveData.AllLevels.Add(CurrentLevelName, FWorldDataSave());

}

void UMiniBenGameInstance::SaveSublevels()
{
	UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();

    MainSaveData.LastSavedLevel = *CurrentLevelName; // save the level 

    if (CustomWorldSubsystem)
    {
       auto CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

        if (CurrentLevelWorldDataSave)
        {
            CurrentLevelWorldDataSave->bHasLevelBeenInitialized = true;

            auto AllSublevels = CustomWorldSubsystem->GetAllSubLevels(GetWorld());
            FString SubLevelName;

            for (const auto& ele : AllSublevels)
            {
                SubLevelName = ULevelStreamingFunctionsUtils::ConvertLevelStreamingInstanceToString(ele);
                CurrentLevelWorldDataSave->ListOfSublevels.Add(SubLevelName, ele->IsLevelVisible());
            }
        }
    }
}

void UMiniBenGameInstance::SavePlayer(const FCharacterStats& PlayerStats)
{
    MainSaveData.PlayerStats = PlayerStats;

    FWorldDataSave* CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

    if (CurrentLevelWorldDataSave)
    {
        ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (PlayerChar)
        {
            CurrentLevelWorldDataSave->PlayerPosition = PlayerChar->GetActorLocation();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SavePlayer - > PlayerChar is nullptr"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SavePlayer CurrentLevelWorldDataSave is nullptr"));
    }
}

//void UMiniBenGameInstance::SaveCurrentWorldAssets()
//{
//    TArray<AActor*> SaveableActors;
//    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveable::StaticClass(), SaveableActors);
//
//    if (SaveableActors.IsEmpty())
//    {
//        UE_LOG(LogTemp, Warning, TEXT("NOT FOUND SaveableActors.IsEmpty()"));
//    }
//
//    for (AActor* ele : SaveableActors)
//    {
//        ISaveable::Execute_SaveAndRecordSelf(ele);
//    }
//}

void UMiniBenGameInstance::AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem)
{
    auto CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

    //NEW WAY, BETTER WAY
    if (CurrentLevelWorldDataSave)
    {
        bool isFound = CurrentLevelWorldDataSave->MapOfLevelWorldItems.Contains(newItem.Guid);
        if (!isFound)
        {
            CurrentLevelWorldDataSave->MapOfLevelWorldItems.Add(newItem.Guid, newItem);
        }
        else
        {
            CurrentLevelWorldDataSave->MapOfLevelWorldItems[newItem.Guid] = newItem;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AddNewWorldAssetToSaveData CurrentLevelWorldDataSave was not found"));
    }
    
}

void UMiniBenGameInstance::AddNPCToSaveData(const FSaveableWorldNpcs& newNpc)
{
    auto CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);
    if (CurrentLevelWorldDataSave)
    {
        bool isFound = CurrentLevelWorldDataSave->MapOfLevelSaveableNpcs.Contains(newNpc.Guid);
        if (!isFound)
        {
            CurrentLevelWorldDataSave->MapOfLevelSaveableNpcs.Add(newNpc.Guid, newNpc);
        }
        else
        {
            CurrentLevelWorldDataSave->MapOfLevelSaveableNpcs[newNpc.Guid] = newNpc;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AddNPCToSaveData CurrentLevelWorldDataSave was not found"));
    }
}

void UMiniBenGameInstance::SavePlayerInventory(const TMap<FName, int32>& inventory)
{
    MainSaveData.PlayerInventory = inventory;
}

void UMiniBenGameInstance::RestorePlayer(FCharacterStats& PlayerStats, FVector& NewPos)
{
    FWorldDataSave* CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

    NewPos = CurrentLevelWorldDataSave->PlayerPosition;
    PlayerStats = MainSaveData.PlayerStats;
}

void UMiniBenGameInstance::RestoreCurrentWorldAssets()
{
    TArray<AActor*> SaveableActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveable::StaticClass(), SaveableActors);

    for (AActor* ele : SaveableActors)
    {
        ISaveable::Execute_LoadAndRestoreSelf(ele);
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
}

void UMiniBenGameInstance::RestorePlayerInventory(TMap<FName, int32>& Outinventory)
{
    Outinventory = MainSaveData.PlayerInventory;
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

void UMiniBenGameInstance::ProcessNextSublevel()
{
    // If the queue is empty, we're done
    if (SublevelQueue.IsEmpty())
    {
      //All sublevels processed
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
        TSoftObjectPtr<UWorld> LevelToLoad = TSoftObjectPtr<UWorld>(FStringAssetReference(LevelPackageName));

        if (NextSublevel.bShouldBeLoaded)
        {
            // Load the sublevel
            UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), LevelToLoad, true, false, LatentInfo);
        }
        else
        {
            // Unload the sublevel
            UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), LevelToLoad, LatentInfo, false);
        }
    }
}

void UMiniBenGameInstance::FinishStreamLevelsFunc()
{
    // Move to the next sublevel in the queue
    ProcessNextSublevel();
}
