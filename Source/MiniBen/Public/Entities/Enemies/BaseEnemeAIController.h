// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemeAIController.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API ABaseEnemeAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseEnemeAIController();
	virtual void BeginPlay() override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
private:
	FGenericTeamId TeamID;
	
};
