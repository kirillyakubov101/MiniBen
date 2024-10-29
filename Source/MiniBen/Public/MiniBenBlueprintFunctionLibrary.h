// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStructs.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MiniBenBlueprintFunctionLibrary.generated.h"

class UCollectableitemsDataAsset;

UCLASS()
class MINIBEN_API UMiniBenBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Saving | Inventory")
	static TMap<FName, int32> ConvertRealInventoryToSerializable(const TMap<UCollectableitemsDataAsset*, int32>& InventoryData);

	UFUNCTION(BlueprintPure, Category = "Saving | Inventory")
	static TMap<UCollectableitemsDataAsset*, int32> ConvertSerializableToRealInventory(const TMap<FName, int32>& InventoryData, const TArray<UObject*>& LoadedDataAssets);

    UFUNCTION(BlueprintCallable, Category = "Utils")
	static int32 FindIndexByGuid(const TArray<FSaveableWorldItem>& Items, const FGuid& Guid);
   
	
};
