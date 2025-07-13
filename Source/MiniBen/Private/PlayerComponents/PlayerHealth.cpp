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
}

void UPlayerHealth::NotifyPlayerDeath()
{
	GameEventsBroker::GetInst().BroadcastPlayerDeath();
}


