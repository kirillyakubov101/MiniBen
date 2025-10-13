// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/RangedCombatHandler.h"
#include <Interfaces/PlayerComponentBroker.h>
#include <Interfaces/PlayerActionPermissions.h>

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

	IPlayerComponentBrokerInterface* Broker = Cast<IPlayerComponentBrokerInterface>(GetOwner());
	if (Broker)
	{

		IPlayerActionPermissions* Permissions = Broker->GetPlayerActionPermissionsNative();
		if (Permissions)
		{
			Permissions->GetOnDynamicUpdateActionState().AddUObject(this, &URangedCombatHandler::ValidateStateContinue);
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
void URangedCombatHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URangedCombatHandler::ValidateStateContinue()
{
	IPlayerComponentBrokerInterface* Broker = Cast<IPlayerComponentBrokerInterface>(GetOwner());

	TScriptInterface<IPlayerActionPermissions> Permissions = IPlayerComponentBrokerInterface::Execute_GetPlayerActionPermissions(GetOwner());
	bool CanStillAttack = IPlayerActionPermissions::Execute_CanPerformAction(Permissions.GetObject(), EPlayerActions::PA_Attacking);
	if(!CanStillAttack)
	{
		TScriptInterface<IPlayerActionPermissions> PlayerActionPermission = IPlayerComponentBrokerInterface::Execute_GetPlayerActionPermissions(GetOwner());
		IPlayerActionPermissions::Execute_SetActionState(PlayerActionPermission.GetObject(), EPlayerActions::PA_Attacking, false);
		SetIsAttackingInRangedForm_Implementation(false);
	}
	
}

void URangedCombatHandler::SetIsAttackingInRangedForm_Implementation(bool bNewIsAttackingInRangedForm)
{
	this->bIsAttacking = bNewIsAttackingInRangedForm;
}

