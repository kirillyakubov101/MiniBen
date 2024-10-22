// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamingBridge.generated.h"

UCLASS()
class LEVELSTREAMINGUTILS_API ALevelStreamingBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelStreamingBridge();

protected:

	UFUNCTION(BlueprintPure)
	bool IsLevelLoaded(const TSoftObjectPtr<UWorld>& LevelPtr) const;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> m_Sublevel_1;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> m_Sublevel_2;

};
