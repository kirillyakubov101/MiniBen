// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyAIRangedCombat.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyAIRangedCombat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IEnemyAIRangedCombat
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIRangedCombat")
	void AnimateRangedWeaponAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIRangedCombat")
	void ShootRangedWeapont();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIRangedCombat")
	void DrawArrowToRightHandFromQuiver();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIRangedCombat")
	void AttachArrowToBowFromRightHand();

};
