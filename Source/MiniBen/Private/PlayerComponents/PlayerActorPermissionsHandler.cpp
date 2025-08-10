// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/PlayerActorPermissionsHandler.h"
#include "MyStructs.h"

UPlayerActorPermissionsHandler::UPlayerActorPermissionsHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerActorPermissionsHandler::BeginPlay()
{
	Super::BeginPlay();

	InitializeActionStates();
}

void UPlayerActorPermissionsHandler::DynamicStateUpdateSignal_Implementation()
{
	if (this->OnDynamicUpdateActionStateDelegate.IsBound())
	{
		this->OnDynamicUpdateActionStateDelegate.Broadcast();
	}
}

void UPlayerActorPermissionsHandler::SetActionState_Implementation(EPlayerActions CharacterAction, bool State)
{
	if (ActionStates.Contains(CharacterAction))
	{
		ActionStates[CharacterAction] = State;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to set state for undefined action: %s"), *UEnum::GetValueAsString(CharacterAction));
	}
}

bool UPlayerActorPermissionsHandler::CanPerformAction_Implementation(EPlayerActions CharacterAction)
{
	bool canPerform = false;

	switch (CharacterAction)
	{
	//Player wants to jump
	case EPlayerActions::PA_Air:
		canPerform =
			ActionStates[EPlayerActions::PA_Air] != true &&
			ActionStates[EPlayerActions::PA_Attacking] != true &&
			ActionStates[EPlayerActions::PA_MidRolling] != true &&
			ActionStates[EPlayerActions::PA_Stagger] != true;		
			break;

	case EPlayerActions::PA_MidRolling:
		canPerform=
			ActionStates[EPlayerActions::PA_Air] != true &&
			ActionStates[EPlayerActions::PA_MidRolling] != true &&
			ActionStates[EPlayerActions::PA_MidSheath] != true &&
			ActionStates[EPlayerActions::PA_Stagger] != true;
		break;

	case EPlayerActions::PA_Attacking:
		canPerform =
			ActionStates[EPlayerActions::PA_Air] != true &&
			ActionStates[EPlayerActions::PA_MidRolling] != true &&
			ActionStates[EPlayerActions::PA_MidSheath] != true &&
			ActionStates[EPlayerActions::PA_Stagger] != true &&
			ActionStates[EPlayerActions::PA_Sheath] == true &&
			ActionStates[EPlayerActions::PA_UnSheath] != true;
		break;

	case EPlayerActions::PA_Dead:
		canPerform = true;
		break;


	case EPlayerActions::PA_Sheath:
		canPerform =
			ActionStates[EPlayerActions::PA_MidRolling] != true &&
			ActionStates[EPlayerActions::PA_MidSheath] != true &&
			ActionStates[EPlayerActions::PA_Stagger] != true &&
			ActionStates[EPlayerActions::PA_Attacking] != true &&
			ActionStates[EPlayerActions::PA_Sheath] != true;
		break;

	case EPlayerActions::PA_UnSheath:
		canPerform =
			ActionStates[EPlayerActions::PA_MidRolling] != true &&
			ActionStates[EPlayerActions::PA_MidSheath] != true &&
			ActionStates[EPlayerActions::PA_Stagger] != true &&
			ActionStates[EPlayerActions::PA_Attacking] != true &&
			ActionStates[EPlayerActions::PA_Sheath] == true;
		break;

	case EPlayerActions::PA_Stagger:
		canPerform =
			ActionStates[EPlayerActions::PA_MidRolling] != true &&
			ActionStates[EPlayerActions::PA_MidSheath] != true &&
			ActionStates[EPlayerActions::PA_Stagger] != true &&
			ActionStates[EPlayerActions::PA_Sheath] == true &&
			ActionStates[EPlayerActions::PA_Air] != true;
		break;
		
	}
	return canPerform;
}

FOnDynamicUpdateActionStateSignatureSignature& UPlayerActorPermissionsHandler::GetOnDynamicUpdateActionState()
{
	return this->OnDynamicUpdateActionStateDelegate;
}


void UPlayerActorPermissionsHandler::InitializeActionStates()
{
	UEnum* Enum = StaticEnum<EPlayerActions>();
	int32 EnumCount = Enum->NumEnums() - 1; // Skip _MAX or hidden values

	for (int32 i = 0; i < EnumCount; ++i)
	{
		EPlayerActions Action = static_cast<EPlayerActions>(i);
		ActionStates.Add(Action, false);
	}

	ActionStates[EPlayerActions::PA_UnSheath] = true;
}

