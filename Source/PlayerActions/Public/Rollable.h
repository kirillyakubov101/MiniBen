// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Rollable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRolled);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URollable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYERACTIONS_API IRollable
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Roll")
	void BindToRollEvent(UObject* Object, FName FunctionName);
};
