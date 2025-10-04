// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/EquipmentHandler.h"
#include "Data/WeaponDataAsset.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include <Interfaces/CharacterMeshInterface.h>
#include "MiniBenCharacter.h"

/// <summary>
/// actor component that handles equipping and unequipping weapons for a character
/// </summary>

UEquipmentHandler::UEquipmentHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEquipmentHandler::BeginPlay()
{
	Super::BeginPlay();

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

void UEquipmentHandler::EquipWeapon_Implementation(UWeaponDataAsset* NewWeapon)
{
	if (!NewWeapon) return;
	LoadedSkeletalMeshWeapon = nullptr;
	CurrentWeapon = NewWeapon;
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh = CurrentWeapon->WeaponSkeletalMesh;

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FSoftObjectPath MeshPath = SkeletalMesh.ToSoftObjectPath();
	ICharacterMeshInterface* CharacterMeshInterface = Cast<ICharacterMeshInterface>(GetOwner());

	switch (NewWeapon->WeaponType)
	{
		case EWeaponType::WT_Fists:
		case EWeaponType::WT_OneHandedWeapon:
			ICombatInterface::Execute_NotifyForNewReadyMeleeWeapon(GetOwner(), NewWeapon);
			break;
		case EWeaponType::WT_Bow:
			ICombatInterface::Execute_NotifyForNewReadyRangedWeapon(GetOwner(), NewWeapon);
			break;
	}

	switch (CurrentWeapon->InactiveEquipmentSocket)
	{
	case EEquipmentSockets::ES_LeftHip:
		RestingSkeletalMeshComp = ICharacterMeshInterface::Execute_GetLeftWeaponHolsterSkeletalMeshComp(GetOwner());
		break;
	case EEquipmentSockets::ES_Back:
		RestingSkeletalMeshComp = ICharacterMeshInterface::Execute_GetBackHolsterSkeletalMeshComp(GetOwner());
		break;
	case EEquipmentSockets::ES_None:
		return;

	 default:
		return;
	}


	if (MeshPath.IsValid())
	{
		Streamable.RequestAsyncLoad(MeshPath, FStreamableDelegate::CreateLambda([this, MeshPath]()
			{
				LoadedSkeletalMeshWeapon = Cast<USkeletalMesh>(MeshPath.ResolveObject());

				if (!LoadedSkeletalMeshWeapon)
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to load weapon mesh at path: %s"), *MeshPath.ToString());
					return;
				}


				if (ensure(RestingSkeletalMeshComp.IsValid()))
				{
					RestingSkeletalMeshComp->SetSkeletalMesh(LoadedSkeletalMeshWeapon);
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
	return nullptr;
}

USkeletalMesh* UEquipmentHandler::GetCurrentWeaponSkeletalMesh_Implementation() const
{
	return LoadedSkeletalMeshWeapon;
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
	if (this->RestingSkeletalMeshComp.IsValid())
	{
		RestingSkeletalMeshComp->SetSkeletalMesh(nullptr);
	}
}

bool UEquipmentHandler::IsNoWeaponAssigned_Implementation() const
{
	return CurrentWeapon == nullptr;
}




