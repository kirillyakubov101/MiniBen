// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStructs.h"
#include "GameFramework/GameModeBase.h"
#include "MiniBenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AMiniBenGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Save")
	FMainSaveData MainSaveDataDev;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AssignSaveData(const FMainSaveData& data);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Save")
	bool GetMainDataFromLoading(FMainSaveData& Outdata);

protected:
	virtual void BeginPlay() override;
	
};
