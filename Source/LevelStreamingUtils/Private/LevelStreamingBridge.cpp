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

// Called when the game starts or when spawned
void ALevelStreamingBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelStreamingBridge::ListAllSubLevels(UWorld* World) const
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

	const TArray<ULevelStreaming*>& ListOfStreamingLevels = CurrentWorld->GetStreamingLevels();

	for (ULevelStreaming* StreamingLevel : ListOfStreamingLevels)
	{
		if (StreamingLevel)
		{
			FString LevelName = StreamingLevel->GetWorldAssetPackageName();
			UE_LOG(LogTemp, Warning, TEXT("Sublevel: %s"), *LevelName);
			bool bIsLevelLoaded = StreamingLevel->IsLevelLoaded();
			UE_LOG(LogTemp, Warning, TEXT("Is level loaded: %s"), bIsLevelLoaded ? TEXT("true") : TEXT("false"));
		}
	}
}

// Called every frame
void ALevelStreamingBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

