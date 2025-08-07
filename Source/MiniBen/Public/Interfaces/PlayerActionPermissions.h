// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyStructs.h"
#include "PlayerActionPermissions.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDynamicUpdateActionStateSignatureSignature);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerActionPermissions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IPlayerActionPermissions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerActionPermissions")
	void DynamicStateUpdateSignal();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerActionPermissions")
	void SetActionState(EPlayerActions CharacterAction, bool State);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerActionPermissions")
	bool CanPerformAction(EPlayerActions CharacterAction);

	virtual FOnDynamicUpdateActionStateSignatureSignature& GetOnDynamicUpdateActionState() = 0;
};
