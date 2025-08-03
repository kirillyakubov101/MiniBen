// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <MyStructs.h>
#include "LocomotionStateMachineInterface.generated.h"


UINTERFACE(MinimalAPI)
class ULocomotionStateMachineInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API ILocomotionStateMachineInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LocomotionStateMachineInterface")
	void SwitchState(EWeaponType WeaponType);
};
