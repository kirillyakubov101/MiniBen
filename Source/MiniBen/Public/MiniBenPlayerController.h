// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiniBenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AMiniBenPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerLoaded();
	
};
