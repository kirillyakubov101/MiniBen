// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/KillsHandler.h"

// Sets default values for this component's properties
UKillsHandler::UKillsHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UKillsHandler::BeginPlay()
{
	Super::BeginPlay();	
}

void UKillsHandler::SignalEnemyKilled_Implementation(TSubclassOf<AGameEntity_Enemy> EnemyClass)
{
	this->OnEnemyKilledDelegate.Broadcast(EnemyClass);
}


