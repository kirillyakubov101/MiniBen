// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <Data/WeaponDataAsset.h>
#include "CombatInterface.generated.h"


/// <summary>
/// Interface for combat-related functionalities, including weapon management and combat actions.
/// </summary>
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API ICombatInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatInterface")
	UWeaponDataAsset* GetCurrentWeapon() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatInterface")
	FTransform GetRightHandTransform() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatInterface")
	void NotifyForNewReadyMeleeWeapon(UWeaponDataAsset* NewWeapon);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatInterface")
	void NotifyForNewReadyRangedWeapon(UWeaponDataAsset* NewWeapon);
};
