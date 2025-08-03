// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../MyStructs.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    // Override the GetPrimaryAssetId function to return the asset ID based on ItemType and ItemID
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(WeaponAssetType, WeaponId);
    }


    const FName GetItemName() const
    {
        return WeaponId;
    }

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FString WeaponDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSoftObjectPtr<UStaticMesh> WeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSoftObjectPtr<UAnimMontage> ReadyWeaponAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSoftObjectPtr<UAnimMontage> LowerWeaponAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TArray<TSoftObjectPtr<UAnimMontage>> ListOfAttacks;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    float DamageAmount;

protected:
    // ItemType defines the category, such as "Collectable" or "Weapon"
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    FPrimaryAssetType WeaponAssetType = "Weapons";

    // ItemID can be any descriptive identifier, like "healing potion" or "mana potion"
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName WeaponId;
	
};
