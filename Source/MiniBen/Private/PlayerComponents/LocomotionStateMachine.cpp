// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/LocomotionStateMachine.h"
#include <Interfaces/StateMachineInterface.h>

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

void ULocomotionStateMachine::SwitchState(EWeaponType WeaponType)
{
	switch (WeaponType)
	{
	case EWeaponType::WT_Fists:
		break;
	case EWeaponType::WT_OneHandedWeapon:
		break;
	case EWeaponType::WT_Unarmed:
		break;
	}

	//Call the owner and let him know!
}

void ULocomotionStateMachine::InitStartState()
{
	IStateMachineInterface* StateMachineInterface = Cast<IStateMachineInterface>(GetOwner());
	if (StateMachineInterface)
	{
		this->CurrentState = IStateMachineInterface::Execute_GetNormalState(GetOwner());
		if (this->CurrentState)
		{
			IState::Execute_EnterState(this->CurrentState.GetObject());
		}
	}
}

void ULocomotionStateMachine::TickState(float DeltaTime)
{
	if (IsValid(CurrentState.GetObject()) && CurrentState.GetInterface() != nullptr)
	{
		IState::Execute_TickState(CurrentState.GetObject(), DeltaTime);
	}
}

void ULocomotionStateMachine::SwitchStateProccess()
{
	
}

