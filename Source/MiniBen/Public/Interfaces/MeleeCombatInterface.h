// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <Data/WeaponDataAsset.h>
#include "MeleeCombatInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMeleeCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IMeleeCombatInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void AssignNewWeapon(UWeaponDataAsset* WeaponData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void AttackCommand();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void RotateCharacterToFaceForward(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void EndSingleTargetTrace();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void BeginSingleTargetTrace();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void ComboEnd();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MeleeCombat")
	void ComboNext();

};
