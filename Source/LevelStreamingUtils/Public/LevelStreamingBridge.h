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
	// Sets default values for this actor's properties
	ALevelStreamingBridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ListAllSubLevels(UWorld* World) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
