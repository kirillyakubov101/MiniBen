// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenBlueprintFunctionLibrary.h"
#include "CollectableitemsDataAsset.h"
#include "Engine/AssetManager.h"


TMap<FName, int32> UMiniBenBlueprintFunctionLibrary::ConvertRealInventoryToSerializable(const TMap<UCollectableitemsDataAsset*, int32>& InventoryData)
{
    TMap<FName, int32> SerializableMap;

    for (const TPair<UCollectableitemsDataAsset*, int32>& ele : InventoryData)
    {
        if (ele.Key)
        {
            SerializableMap.Add(ele.Key->GetItemName(), ele.Value);
        }
    }

    return SerializableMap;
}

TMap<UCollectableitemsDataAsset*, int32> UMiniBenBlueprintFunctionLibrary::ConvertSerializableToRealInventory(const TMap<FName, int32>& InventoryData, const TArray<UObject*>& LoadedDataAssets)
{
    TMap<UCollectableitemsDataAsset*, int32> InventoryMap;

    for (UObject* Obj : LoadedDataAssets)
    {
        // Attempt to cast the object to UCollectableitemsDataAsset
        UCollectableitemsDataAsset* ItemAsset = Cast<UCollectableitemsDataAsset>(Obj);
        if (ItemAsset)
        {
            // Get the item's name (ItemID) and quantity if applicable
            FName ItemName = ItemAsset->GetItemName();

            // Check if this name exists in InventoryData
            const int32* QuantityPtr = InventoryData.Find(ItemName);
            if (QuantityPtr)
            {
                // If found, add the asset and the quantity to InventoryMap
                InventoryMap.Add(ItemAsset, *QuantityPtr);
            }
        }
    }

    return InventoryMap;
}
