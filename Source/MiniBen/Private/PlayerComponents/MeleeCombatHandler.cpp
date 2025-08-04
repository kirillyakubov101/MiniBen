// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/MeleeCombatHandler.h"
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

	if (bIsAttackMidway)
	{
		RotateCharacterToFaceForward_Implementation(DeltaTime);
	}

	
}

void UMeleeCombatHandler::AssignNewWeapon_Implementation(UWeaponDataAsset* WeaponData)
{
	this->CurrentWeapon = WeaponData;

}

void UMeleeCombatHandler::AttackCommand_Implementation()
{
}

void UMeleeCombatHandler::RotateCharacterToFaceForward_Implementation(float DeltaTime)
{
	// Get camera forward vector and convert to yaw-only rotation (ignore pitch and roll)
	FVector CameraForward = IPlayerComponentBrokerInterface::Execute_GetPlayerCameraForward(GetOwner());
	FRotator TargetRotation = CameraForward.ToOrientationRotator();
	TargetRotation.Pitch = 0.0f;
	TargetRotation.Roll = 0.0f;

	// Get current actor rotation
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	// Interpolate towards the target rotation
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationTowardsCameraForwardSpeed);

	// Set the new rotation
	GetOwner()->SetActorRotation(NewRotation);
}

void UMeleeCombatHandler::EndSingleTargetTrace_Implementation()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(AttackTraceTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTraceTimer);
	}
}

void UMeleeCombatHandler::BeginSingleTargetTrace_Implementation()
{
		GetWorld()->GetTimerManager().SetTimer(
			AttackTraceTimer,
			this,
			&UMeleeCombatHandler::TraceSingal,
			0.01f,
			true
		);
}

void UMeleeCombatHandler::ComboEnd_Implementation()
{
	bIsAttackQueued = false;
	bIsAttackMidway = false;
	CurrentAttackIndex = 0;
	TScriptInterface<IPlayerActionPermissions> PlayerActionPermission = IPlayerComponentBrokerInterface::Execute_GetPlayerActionPermissions(GetOwner());
	IPlayerActionPermissions::Execute_SetActionState(PlayerActionPermission.GetObject(), EPlayerActions::PA_Attacking, false);
	SetComponentTickEnabled(false);
}

void UMeleeCombatHandler::ComboNext_Implementation()
{
	CurrentAttackIndex++;
	if (CurrentAttackIndex > AmountOfAttacks)
	{
		ComboEnd_Implementation();
	}
	else
	{
		if (bIsAttackQueued)
		{
			bIsAttackQueued = false;
			PlayAttackSequanceEvent();
		}
	}

}

void UMeleeCombatHandler::PlayAttackSequanceEvent()
{
}

void UMeleeCombatHandler::TraceSingal()
{
}

void UMeleeCombatHandler::LoadAttackAnimations()
{

}

