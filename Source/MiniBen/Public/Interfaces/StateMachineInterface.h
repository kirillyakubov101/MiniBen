// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerComponents/LocomotionStateMachine.h"
#include "State.h"
#include "StateMachineInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStateMachineInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IStateMachineInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateMachine")
	TScriptInterface<ILocomotionStateMachineInterface> GetStateMachine() const;
};
