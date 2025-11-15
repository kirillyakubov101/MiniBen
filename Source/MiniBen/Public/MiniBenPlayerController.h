// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MiniBenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AMiniBenPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(0); }
protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerLoaded();

	
};
