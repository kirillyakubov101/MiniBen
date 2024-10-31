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
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
}

void UMiniBenGameInstance::OnLevelChanged(UWorld* LoadedWorld)
{
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    InitCurrentWorld();
    BeginLoadLevelProcess();
}

//First Empty Init entry to the save data file
void UMiniBenGameInstance::InitCurrentWorld()
{
    if (MainSaveData.AllLevels.Contains(CurrentLevelName)) { return; }

	MainSaveData.AllLevels.Add(CurrentLevelName, FWorldDataSave());

}

void UMiniBenGameInstance::SaveSublevels()
{
	UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();

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
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("NOT FOUND"));
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

void UMiniBenGameInstance::SaveCurrentWorldAssets()
{
    TArray<AActor*> SaveableActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveable::StaticClass(), SaveableActors);

    if (SaveableActors.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("NOT FOUND SaveableActors.IsEmpty()"));
    }

    for (AActor* ele : SaveableActors)
    {
        ISaveable::Execute_SaveAndRecordSelf(ele);
    }
}

void UMiniBenGameInstance::AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem)
{
    auto CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);
    if (CurrentLevelWorldDataSave)
    {
        int32 foundItem = CurrentLevelWorldDataSave->ListOfLevelAssets.Find(newItem);

        if (foundItem == INDEX_NONE)
        {
            CurrentLevelWorldDataSave->ListOfLevelAssets.Add(newItem);
        }
        else
        {
            CurrentLevelWorldDataSave->ListOfLevelAssets[foundItem] = newItem;
        }
    }
   
}

void UMiniBenGameInstance::RestorePlayer(FCharacterStats& PlayerStats, FVector& NewPos)
{
    FWorldDataSave* CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

    NewPos = CurrentLevelWorldDataSave->PlayerPosition;
    PlayerStats = MainSaveData.PlayerStats;
}

void UMiniBenGameInstance::RestoreCurrentWorldAssets()
{

}

void UMiniBenGameInstance::RestoreSublevels()
{
    // Check if there is saved data to restore
    if (!MainSaveData.bHasSaved)
    {
        UE_LOG(LogTemp, Warning, TEXT("!MainSaveData.bHasSaved"));
        return;
    }

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
