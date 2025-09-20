// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RangedCombatInterface.generated.h"

/// <summary>
/// range combat interface for ranged weapon functionalities, including weapon assignment and attack commands.
/// </summary>
UINTERFACE(MinimalAPI)
class URangedCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IRangedCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RangedCombatInterface")
	void AssignNewWeapon(class UWeaponDataAsset* WeaponData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RangedCombatInterface")
	bool IsAttackingInRangedForm() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RangedCombatInterface")
	void SetIsAttackingInRangedForm(bool bNewIsAttackingInRangedForm);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RangedCombatInterface")
	void AttackCommand();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void RotateCharacterToFaceForward(float DeltaTime);
};
