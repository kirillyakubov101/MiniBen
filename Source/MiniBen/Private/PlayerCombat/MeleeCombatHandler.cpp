// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCombat/MeleeCombatHandler.h"
#include "Interfaces/PlayerComponentBroker.h"
#include "Interfaces/PlayerActionPermissions.h"

// Sets default values for this component's properties
UMeleeCombatHandler::UMeleeCombatHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeleeCombatHandler::BeginPlay()
{
	Super::BeginPlay();

	IPlayerComponentBrokerInterface* Broker = Cast<IPlayerComponentBrokerInterface>(GetOwner());
	if (Broker)
	{
		
		IPlayerActionPermissions* Permissions = Broker->GetPlayerActionPermissionsNative();
		if (Permissions)
		{
			Permissions->GetOnDynamicUpdateActionState().AddUObject(this, &UMeleeCombatHandler::ProccessDynamicActionSignal);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Permissions is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Broker is null"));
	}
	
}


// Called every frame
void UMeleeCombatHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMeleeCombatHandler::AssignNewWeapon_Implementation(UWeaponDataAsset* WeaponData)
{
}

void UMeleeCombatHandler::AttackCommand_Implementation()
{
}

void UMeleeCombatHandler::RotateCharacterToFaceForward_Implementation(float DeltaTime)
{
}

