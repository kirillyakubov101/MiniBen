// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/RangedCombatHandler.h"

// Sets default values for this component's properties
URangedCombatHandler::URangedCombatHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URangedCombatHandler::BeginPlay()
{
	Super::BeginPlay();

	// TODO: sub to the OnDynamicUpdateActionStateDelegate of the PlayerActionPermissions to Update attack state
	
}


// Called every frame
void URangedCombatHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

