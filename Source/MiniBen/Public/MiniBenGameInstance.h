// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStructs.h"
#include "Engine/GameInstance.h"
#include "MiniBenGameInstance.generated.h"


UCLASS()
class MINIBEN_API UMiniBenGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveCurrentWorld();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveSublevels();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SavePlayer();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveCurrentWorldAssets();

protected:
	UPROPERTY()
	FString CurrentLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	FMainSaveData MainSaveData;
	
};
