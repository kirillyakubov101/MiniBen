// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/PlayerHealth.h"
#include "GameEventsBroker.h"

// Sets default values for this component's properties
UPlayerHealth::UPlayerHealth()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	this->CurrentPlayerHealth = this->MaxPlayerHealth;
}

void UPlayerHealth::NotifyPlayerDeath()
{
	GameEventsBroker::GetInst().BroadcastPlayerDeath();
}

void UPlayerHealth::DecreaseHealth(float DamageAmount)
{
	CurrentPlayerHealth = FMath::Max(0.f, CurrentPlayerHealth - DamageAmount);

	if (IsDead())
	{
		//implement deathState
		UseDeathState();
	}
	else if(ShouldStaggerPlayer())
	{
		UseStaggerState();
	}
}

bool UPlayerHealth::IsDead()
{
	return this->CurrentPlayerHealth <= 0.f;
}

bool UPlayerHealth::ShouldStaggerPlayer()
{
	return FMath::FRand() <= this->ChanceToStaggerPlayer;
}


