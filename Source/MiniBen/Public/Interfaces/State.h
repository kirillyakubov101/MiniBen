// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "State.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void EnterState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void ExitState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void TickState(float DeltaTime);

};
