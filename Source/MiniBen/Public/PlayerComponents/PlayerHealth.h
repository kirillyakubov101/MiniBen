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

	UFUNCTION(BlueprintCallable, Category = "Health")
	void DecreaseHealth(float DamageAmount);

	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsDead();

	UFUNCTION(BlueprintPure, Category = "Health")
	bool ShouldStaggerPlayer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UseStaggerState();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UseDeathState();

protected:

	UPROPERTY(EditAnywhere)
	float CurrentPlayerHealth;

	UPROPERTY(EditAnywhere)
	float MaxPlayerHealth;

	UPROPERTY(EditAnywhere)
	float ChanceToStaggerPlayer;
	
};	
