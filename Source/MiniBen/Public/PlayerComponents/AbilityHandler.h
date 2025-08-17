// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "../../../PlayerActions/Public/Saveable.h"
#include "AbilityHandler.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIBEN_API UAbilityHandler : public UActorComponent, public ISaveable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FGameplayTag,bool> Abilities;

	UFUNCTION(BlueprintCallable)
	void AddAbility(FGameplayTag NewAbility, bool IsActive);

	UFUNCTION(BlueprintCallable)
	void ActivateAbility(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable)
	void DeactivateAbility(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable)
	bool HasAbility(FGameplayTag AbilityTag) const;

	UFUNCTION(BlueprintPure)
	bool IsAbilityActive(FGameplayTag AbilityTag) const;



};
