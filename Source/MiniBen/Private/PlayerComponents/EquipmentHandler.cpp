// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/EquipmentHandler.h"
#include "Data/WeaponDataAsset.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include <Interfaces/CharacterMeshInterface.h>
#include <Interfaces/StateMachineInterface.h>

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

	//Notify Combat Handler !
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FSoftObjectPath MeshPath = Mesh.ToSoftObjectPath();

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

				ICharacterMeshInterface* CharacterMeshInterface = Cast<ICharacterMeshInterface>(GetOwner());
				check(CharacterMeshInterface);

				UStaticMeshComponent* StaticMesh = ICharacterMeshInterface::Execute_GetLeftWeaponHolsterStaticMeshComp(GetOwner());

				if (StaticMesh)
				{
					StaticMesh->SetStaticMesh(LoadedMesh);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent was null."));
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
	LocomotionStateMachine->SwitchState(WeaponType);
}

void UEquipmentHandler::LowerWeapon_Implementation()
{
	bIsWeaponSheathed = false;

	LocomotionStateMachine->SwitchState(EWeaponType::WT_Unarmed);
}

EWeaponType UEquipmentHandler::GetCurrentlyEquippedWeaponType_Implementation() const
{
	return CurrentWeapon->WeaponType;
}

UWeaponDataAsset* UEquipmentHandler::GetCurrentWeapon_Implementation() const
{
	return CurrentWeapon;
}


// Called when the game starts
void UEquipmentHandler::BeginPlay()
{
	Super::BeginPlay();


	IStateMachineInterface* StateMachineInterface = Cast<IStateMachineInterface>(GetOwner());
	if (!StateMachineInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEquipmentHandler: GetOwner does not implement StateMachineInterface"));
		return;
	}

	LocomotionStateMachine = IStateMachineInterface::Execute_GetStateMachine(GetOwner());

	if (!LocomotionStateMachine)
	{
		UE_LOG(LogTemp, Warning, TEXT("LocomotionStateMachine IS nullptr"));
	}
	
}


