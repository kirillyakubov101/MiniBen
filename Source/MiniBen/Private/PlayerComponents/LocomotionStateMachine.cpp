// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/LocomotionStateMachine.h"
#include <Interfaces/StateMachineInterface.h>
#include "Interfaces/CombatStateInterface.h"

// Sets default values for this component's properties
ULocomotionStateMachine::ULocomotionStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULocomotionStateMachine::BeginPlay()
{
	Super::BeginPlay();
	InitStartState();
	
}


// Called every frame
void ULocomotionStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickState(DeltaTime);
}

void ULocomotionStateMachine::SwitchState_Implementation(EWeaponType WeaponType)
{
	TScriptInterface<IState> NewState;

	switch (WeaponType)
	{
	case EWeaponType::WT_Fists:
		NewState = ICombatStateInterface::Execute_GetFistCombatState(GetOwner());
		break;
	case EWeaponType::WT_OneHandedWeapon:
		NewState = ICombatStateInterface::Execute_GetOneHandedCombatState(GetOwner());
		break;
	case EWeaponType::WT_Unarmed:
		NewState = ICombatStateInterface::Execute_GetNormalState(GetOwner());
		break;
	}
	SwitchStateProccess(NewState);
}



void ULocomotionStateMachine::InitStartState()
{
	IStateMachineInterface* StateMachineInterface = Cast<IStateMachineInterface>(GetOwner());
	if (StateMachineInterface)
	{
		this->CurrentState = ICombatStateInterface::Execute_GetNormalState(GetOwner());
		if (this->CurrentState)
		{
			IState::Execute_EnterState(this->CurrentState.GetObject());
		}
	}
}

void ULocomotionStateMachine::TickState(float DeltaTime)
{
	IState::Execute_TickState(CurrentState.GetObject(), DeltaTime);
}

void ULocomotionStateMachine::SwitchStateProccess(TScriptInterface<IState> NewState)
{
	if (IsValid(CurrentState.GetObject()))
	{
		IState::Execute_ExitState(CurrentState.GetObject());
	}

	CurrentState = NewState;
	IState::Execute_EnterState(CurrentState.GetObject());
}

