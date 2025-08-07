// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyStructs.h"
#include "CharacterMovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API ICharacterMovementInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterMovementInterface")
	void SetCharMoveSpeed(EPlayerMovementState NewMovementState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterMovementInterface")
	EPlayerMovementState GetCurrentLocomotionState() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterMovementInterface")
	void ToggleMovement(bool bCanMove);

	/*virtual void SetCharMoveSpeed(EPlayerMovementState NewMovementState) = 0;
	virtual EPlayerMovementState GetCurrentLocomotionState() const = 0;
	virtual void ToggleMovement(bool bEnable) = 0;*/
};
