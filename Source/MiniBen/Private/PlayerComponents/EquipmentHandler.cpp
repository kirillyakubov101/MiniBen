// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/EquipmentHandler.h"
#include "Data/WeaponDataAsset.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

// Sets default values for this component's properties
UEquipmentHandler::UEquipmentHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEquipmentHandler::EquipWeapon(UWeaponDataAsset* NewWeapon)
{
	CurrentWeapon = NewWeapon;
	TSoftObjectPtr<UStaticMesh> Mesh = CurrentWeapon->WeaponMesh;

	//Notify Combat Handler !
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	if (Mesh.ToSoftObjectPath().IsValid())
	{
		auto handle = Streamable.RequestAsyncLoad(Mesh.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([Mesh]()
			{
				if (Mesh.IsValid())
				{
					UStaticMesh* LoadedMesh = Mesh.Get();

					//Apply the static mesh to player left holster for weapons | based on the weapon!
				}
			}));
	}
}

UStaticMesh* UEquipmentHandler::GetCurrentWeaponMesh() const
{
	return nullptr;
}

bool UEquipmentHandler::IsWeaponReady() const
{
	return false;
}

void UEquipmentHandler::ReadyWeapon()
{
}

void UEquipmentHandler::LowerWeapon()
{
}

EWeaponType UEquipmentHandler::GetCurrentlyEquippedWeaponType() const
{
	return this->CurrentWeapon->WeaponType;
}


// Called when the game starts
void UEquipmentHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

