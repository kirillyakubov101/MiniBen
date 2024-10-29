// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Saveable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class USaveable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYERACTIONS_API ISaveable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "Saving")
	void SaveAndRecordSelf();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Saving")
	void LoadAndRestoreSelf();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Saving")
	bool ShouldBeRemoved() const;
	virtual bool ShouldBeRemoved_Implemetation() const = 0;
};
