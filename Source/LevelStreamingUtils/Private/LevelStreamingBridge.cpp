// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamingBridge.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelStreamingBridge::ALevelStreamingBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


bool ALevelStreamingBridge::IsLevelLoaded(const TSoftObjectPtr<UWorld>& LevelPtr) const
{
	UWorld* World = GetWorld();

	if (World && LevelPtr.IsValid())
	{
		const TArray<ULevelStreaming*>& ListOfStreamingLevels = World->GetStreamingLevels();
		FString LevelName = LevelPtr.GetLongPackageName();

		for (ULevelStreaming* StreamingLevel : ListOfStreamingLevels)
		{
			if (StreamingLevel && StreamingLevel->GetWorldAssetPackageName().Contains(LevelName))
			{
				return StreamingLevel->IsLevelLoaded();
			}
		}
	}

	return false;
}
