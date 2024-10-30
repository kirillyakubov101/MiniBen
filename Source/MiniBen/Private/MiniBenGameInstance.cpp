// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <LevelStreamingUtils/Public/CustomWorldSubsystem.h>
#include <LevelStreamingUtils/Public/LevelStreamingFunctionsUtils.h>

void UMiniBenGameInstance::SaveCurrentWorld()
{
	CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	MainSaveData.AllLevels.Add(CurrentLevelName, FWorldDataSave());
}

void UMiniBenGameInstance::SaveSublevels()
{
	UCustomWorldSubsystem* CustomWorldSubsystem = GetWorld()->GetSubsystem<UCustomWorldSubsystem>();
    CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

    if (CustomWorldSubsystem)
    {
       auto CurrentLevelWorldDataSave = MainSaveData.AllLevels.Find(CurrentLevelName);

        if (CurrentLevelWorldDataSave)
        {
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

void UMiniBenGameInstance::SavePlayer()
{
}

void UMiniBenGameInstance::SaveCurrentWorldAssets()
{
}
