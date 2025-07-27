// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWorldSubsystem.h"

const TArray<ULevelStreaming*>& UCustomWorldSubsystem::GetAllSubLevels(UWorld* World) const
{
	UWorld* CurrentWorld = nullptr;

	if (World == nullptr)
	{
		CurrentWorld = GetWorld();
	}
	else
	{
		CurrentWorld = World;
	}
	check(CurrentWorld);

	return CurrentWorld->GetStreamingLevels();
}
// DEPRECATED
//TArray<AActor*> UCustomWorldSubsystem::GetAllActorsInSublevel(TSoftObjectPtr<UWorld> Sublevel) const
//{
//    TArray<AActor*> ActorsInSublevel;
//
//    // Ensure the soft pointer is valid and resolved
//    if (Sublevel.IsValid())
//    {
//        // Find the associated level streaming instance
//        UWorld* World = GetWorld();
//        if (!World) return ActorsInSublevel;
//
//        for (ULevelStreaming* LevelStreaming : World->GetStreamingLevels())
//        {
//            if (LevelStreaming && LevelStreaming->GetWorldAsset() == Sublevel)
//            {
//                ULevel* LoadedLevel = LevelStreaming->GetLoadedLevel();
//                if (LoadedLevel)
//                {
//                    ActorsInSublevel = LoadedLevel->Actors;
//                }
//                break; // Found the matching level, no need to continue
//            }
//        }
//    }
//
//    return ActorsInSublevel;
//}
