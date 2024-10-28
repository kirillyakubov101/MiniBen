// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CollectableitemsDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MINIBEN_API UCollectableitemsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	// ItemType defines the category, such as "Collectable" or "Weapon"
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FPrimaryAssetType ItemType = "Collectable";

    // Override the GetPrimaryAssetId function to return the asset ID based on ItemType and ItemID
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(ItemType, ItemID);
    }


    const FName GetItemName() const
    {
        return ItemID;
    }

protected:
    // ItemID can be any descriptive identifier, like "healing potion" or "mana potion"
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FName ItemID;
};
