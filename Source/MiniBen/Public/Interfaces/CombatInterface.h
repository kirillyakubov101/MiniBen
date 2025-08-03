// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <Data/WeaponDataAsset.h>
#include "CombatInterface.generated.h"


// This class does not need to be modified.
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
	void NotifyForNewReadyWeapon(UWeaponDataAsset* NewWeapon);
};
