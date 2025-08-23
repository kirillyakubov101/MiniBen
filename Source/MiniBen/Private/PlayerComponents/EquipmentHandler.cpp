// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/EquipmentHandler.h"
#include "Data/WeaponDataAsset.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include <Interfaces/CharacterMeshInterface.h>
#include "MiniBenCharacter.h"

// Sets default values for this component's properties
UEquipmentHandler::UEquipmentHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEquipmentHandler::EquipWeapon_Implementation(UWeaponDataAsset* NewWeapon)
{
	if (!NewWeapon) return;
	CurrentWeapon = NewWeapon;
	TSoftObjectPtr<UStaticMesh> Mesh = CurrentWeapon->WeaponMesh;

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FSoftObjectPath MeshPath = Mesh.ToSoftObjectPath();

	ICombatInterface::Execute_NotifyForNewReadyWeapon(GetOwner(), NewWeapon);

	ICharacterMeshInterface* CharacterMeshInterface = Cast<ICharacterMeshInterface>(GetOwner());

	switch (CurrentWeapon->InactiveEquipmentSocket)
	{
	case EEquipmentSockets::ES_LeftHip:
		InactiveStaticMeshComp = ICharacterMeshInterface::Execute_GetLeftWeaponHolsterStaticMeshComp(GetOwner());
		break;
	case EEquipmentSockets::ES_Back:
		InactiveStaticMeshComp = ICharacterMeshInterface::Execute_GetBackWeaponStaticMeshComp(GetOwner());
		break;
	case EEquipmentSockets::ES_None:
		return;
	}


	if (MeshPath.IsValid())
	{
		Streamable.RequestAsyncLoad(MeshPath, FStreamableDelegate::CreateLambda([this, MeshPath]()
			{
				LoadedMesh = Cast<UStaticMesh>(MeshPath.ResolveObject());

				if (!LoadedMesh)
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to load weapon mesh at path: %s"), *MeshPath.ToString());
					return;
				}


				if (ensure(InactiveStaticMeshComp.IsValid()))
				{
					InactiveStaticMeshComp->SetStaticMesh(LoadedMesh);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("InactiveStaticMeshComp was noy valid."));
				}
			}));
	}
}

UStaticMesh* UEquipmentHandler::GetCurrentWeaponMesh_Implementation() const
{
	return LoadedMesh;
}

bool UEquipmentHandler::IsWeaponReady_Implementation() const
{
	return bIsWeaponSheathed;
}

void UEquipmentHandler::ReadyWeapon_Implementation()
{
	bIsWeaponSheathed = true;
	EWeaponType WeaponType = CurrentWeapon->WeaponType;
	ILocomotionStateMachineInterface::Execute_SwitchState(LocomotionStateMachine.GetObject(), WeaponType);
}

void UEquipmentHandler::LowerWeapon_Implementation()
{
	bIsWeaponSheathed = false;
	ILocomotionStateMachineInterface::Execute_SwitchState(LocomotionStateMachine.GetObject(), EWeaponType::WT_Unarmed);
}

EWeaponType UEquipmentHandler::GetCurrentlyEquippedWeaponType_Implementation() const
{
	return CurrentWeapon->WeaponType;
}

UWeaponDataAsset* UEquipmentHandler::GetCurrentWeapon_Implementation() const
{
	return CurrentWeapon;
}

void UEquipmentHandler::UnequipWeapon_Implementation()
{
	this->CurrentWeapon = nullptr;
	this->LowerWeapon_Implementation();
	if (this->InactiveStaticMeshComp.IsValid())
	{
		InactiveStaticMeshComp->SetStaticMesh(nullptr);
	}
}

bool UEquipmentHandler::IsNoWeaponAssigned_Implementation() const
{
	return CurrentWeapon == nullptr;
}

// Called when the game starts
void UEquipmentHandler::BeginPlay()
{
	Super::BeginPlay();

	/*if (GetOwner()->GetClass()->ImplementsInterface(UPlayerComponentBrokerInterface::StaticClass()))
	{
		LocomotionStateMachine = IPlayerComponentBrokerInterface::Execute_GetStateMachine(GetOwner());
	}*/

	IPlayerComponentBrokerInterface* Broker = Cast<IPlayerComponentBrokerInterface>(GetOwner());
	if (Broker)
	{
		LocomotionStateMachine = Broker->GetStateMachineNative();
	}
	
	if (!LocomotionStateMachine)
	{
		UE_LOG(LogTemp, Warning, TEXT("LocomotionStateMachine IS nullptr"));
	}
	
}


