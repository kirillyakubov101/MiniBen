// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <LevelStreamingUtils/Public/CustomWorldSubsystem.h>
#include <LevelStreamingUtils/Public/LevelStreamingFunctionsUtils.h>
#include "PlayerActions/Public/Saveable.h"

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
}

void UMiniBenGameInstance::SaveCurrentWorldAssets()
{
    TArray<AActor*> SaveableActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveable::StaticClass(), SaveableActors);

    if (SaveableActors.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("NOT FOUND"));
    }

    for (AActor* ele : SaveableActors)
    {
        ISaveable::Execute_SaveAndRecordSelf(ele);
    }
}

void UMiniBenGameInstance::AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem)
{
    auto CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);
    if(CurrentLevelWorldDataSave == nullptr){ UE_LOG(LogTemp, Warning, TEXT("CurrentLevelWorldDataSave NOT FOUND")); }

    auto foundItem = CurrentLevelWorldDataSave->ListOfLevelAssets.Find(newItem);
    if (foundItem == INDEX_NONE)
    {
        CurrentLevelWorldDataSave->ListOfLevelAssets.Add(newItem);
    }
    else
    {
        CurrentLevelWorldDataSave->ListOfLevelAssets[foundItem] = newItem;
    }
}

void UMiniBenGameInstance::RestorePlayer()
{
}

void UMiniBenGameInstance::RestoreCurrentWorldAssets()
{
}

void UMiniBenGameInstance::RestoreSublevels()
{
    if (!MainSaveData.bHasSaved)
    {
        UE_LOG(LogTemp, Warning, TEXT("!MainSaveData.bHasSaved"));
        return;
    }

    UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();
    FWorldDataSave* CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

    if (CurrentLevelWorldDataSave && CustomWorldSubsystem && CurrentLevelWorldDataSave->bHasLevelBeenInitialized)
    {
        TArray<ULevelStreaming*> AllSubLevels = CustomWorldSubsystem->GetAllSubLevels(GetWorld());

        for (ULevelStreaming* ele : AllSubLevels)
        {
            FString SublevelName = ULevelStreamingFunctionsUtils::ConvertLevelStreamingInstanceToString(ele);
            bool* SublevelState = CurrentLevelWorldDataSave->ListOfSublevels.Find(SublevelName);
            /*FString LevelPackageName = ele->GetWorldAssetPackageName();
            TSoftObjectPtr<UWorld> LevelToLoad = TSoftObjectPtr<UWorld>(FStringAssetReference(LevelPackageName));*/

            int32 state = static_cast<int32>(*SublevelState);
          
            if (state == 1)
            {
                FLatentActionInfo LatentInfo;
                LatentInfo.ExecutionFunction = FName("FinishStreamLevelsFunc");
                LatentInfo.CallbackTarget = this;
                LatentInfo.Linkage = 0;
                LatentInfo.UUID = FMath::Rand();
                UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), ele->GetLoadedLevel(), true, false, LatentInfo);

            }
            else
            {
                FLatentActionInfo LatentInfo;
                LatentInfo.UUID = FMath::Rand();
                LatentInfo.ExecutionFunction = FName("FinishStreamLevelsFunc");
                LatentInfo.CallbackTarget = this;
                LatentInfo.Linkage = 0;
                UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), ele->GetLoadedLevel(), LatentInfo, false);
            }
        }
    }
}

void UMiniBenGameInstance::FinishStreamLevelsFunc()
{
    UE_LOG(LogTemp, Warning, TEXT("FINISH"));
}
