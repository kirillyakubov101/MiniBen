// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KillHandlerInterface.generated.h"

class AGameEntity_Enemy;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyKilledDelegate, TSubclassOf<AGameEntity_Enemy>);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UKillHandlerInterface : public UInterface
{
	GENERATED_BODY()
};


class MINIBEN_API IKillHandlerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerComponents")
	void SignalEnemyKilled(TSubclassOf<AGameEntity_Enemy> EnemyClass);

	virtual void SignalEnemyKilledSignalEnemyKilledNative(TSubclassOf<AGameEntity_Enemy> EnemyClass) = 0;

	static FOnEnemyKilledDelegate OnEnemyKilledDelegate;
};
