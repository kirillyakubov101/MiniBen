// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/AbilityHandler.h"

UAbilityHandler::UAbilityHandler()
{
	
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAbilityHandler::BeginPlay()
{
	Super::BeginPlay();
}

void UAbilityHandler::AddAbility(FGameplayTag NewAbility,bool IsActive)
{
	this->Abilities.Add(NewAbility, IsActive);
}

void UAbilityHandler::ActivateAbility(FGameplayTag AbilityTag)
{
	if (this->Abilities.Contains(AbilityTag))
	{
		this->Abilities[AbilityTag] = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ActivateAbility no ability was found with this %s tag"), *AbilityTag.ToString());
	}
}

void UAbilityHandler::DeactivateAbility(FGameplayTag AbilityTag)
{
	if (this->Abilities.Contains(AbilityTag))
	{
		this->Abilities[AbilityTag] = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DeactivateAbility no ability was found with this %s tag"), *AbilityTag.ToString());
	}
}

bool UAbilityHandler::HasAbility(FGameplayTag AbilityTag) const
{
	return this->Abilities.Contains(AbilityTag);
}

bool UAbilityHandler::IsAbilityActive(FGameplayTag AbilityTag) const
{
	if (this->Abilities.Contains(AbilityTag))
	{
		return this->Abilities[AbilityTag];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IsAbilityActive no ability was found with this %s tag"), *AbilityTag.ToString());
		return false;
	}
}


