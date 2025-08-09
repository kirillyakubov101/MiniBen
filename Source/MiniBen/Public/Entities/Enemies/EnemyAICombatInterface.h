// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyAICombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyAICombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IEnemyAICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAICombat")
	void SheathWeapon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAICombat")
	void UnSheathWeapon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAICombat")
	bool IsWeaponReady() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAICombat")
	void AttackPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAICombat")
	void BeginMeleeTrace();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAICombat")
	void EndMeleeTrace();

};
