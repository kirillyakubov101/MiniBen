// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class MINIBEN_API UPlayerHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPlayerHealth();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Death")
	void NotifyPlayerDeath();


		
};	
