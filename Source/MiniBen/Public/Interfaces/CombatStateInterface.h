// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyStructs.h"
#include "State.h"
#include "CombatStateInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API ICombatStateInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatState")
	EWeaponType GetWeaponTypeBasedOnCombatState() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatState")
	TScriptInterface<IState> GetOneHandedCombatState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatState")
	TScriptInterface<IState> GetFistCombatState();

	//virtual IState* GetFistCombatState() const = 0;
	//virtual IState* GetOneHandedCombatState() const = 0;
	//virtual EWeaponType* GetWeaponTypeBasedOnCombatStateNative() const = 0;
};
