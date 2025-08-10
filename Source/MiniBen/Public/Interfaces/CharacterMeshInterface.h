// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterMeshInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCharacterMeshInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API ICharacterMeshInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterMesh")
	USkeletalMeshComponent* GetCharacterSkeletalMesh() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterMesh")
	UStaticMeshComponent* GetLeftWeaponHolsterStaticMeshComp() const;

	//virtual USkeletalMeshComponent* GetSkeletalMeshComponent() const = 0;
	//virtual UStaticMeshComponent* GetLeftWeaponHolsterStaticMeshComp() const = 0;
};
