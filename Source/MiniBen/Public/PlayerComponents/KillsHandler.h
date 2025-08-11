// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Entities/GameEntity_Enemy.h"
#include "../Interfaces/KillHandlerInterface.h"
#include "KillsHandler.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class MINIBEN_API UKillsHandler : public UActorComponent, public IKillHandlerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKillsHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void SignalEnemyKilled_Implementation(TSubclassOf<AGameEntity_Enemy> EnemyClass);
	virtual void SignalEnemyKilledSignalEnemyKilledNative(TSubclassOf<AGameEntity_Enemy> EnemyClass) override;
};
