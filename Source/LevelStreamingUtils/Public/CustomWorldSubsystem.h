// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CustomWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMINGUTILS_API UCustomWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	const TArray<ULevelStreaming*>& GetAllSubLevels(UWorld* World) const;

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetAllActorsInSublevel(TSoftObjectPtr<UWorld> Sublevel) const;
	
};
