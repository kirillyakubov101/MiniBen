// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/EquipmentInterface.h"
#include "EquipmentHandler.generated.h"


class UWeaponDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API UEquipmentHandler : public UActorComponent, public IEquipmentInterface
{
	GENERATED_BODY()

public:	
	UEquipmentHandler();

	// IEquipmentInterface
	void EquipWeapon_Implementation(UWeaponDataAsset* NewWeapon);
	UStaticMesh* GetCurrentWeaponMesh_Implementation() const;
	bool IsWeaponReady_Implementation() const;
	void ReadyWeapon_Implementation();
	void LowerWeapon_Implementation();
	EWeaponType GetCurrentlyEquippedWeaponType_Implementation() const;
	UWeaponDataAsset* GetCurrentWeapon_Implementation() const;


protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsWeaponSheathed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWeaponDataAsset* CurrentWeapon;

private:
	class ULocomotionStateMachine* LocomotionStateMachine;
	UStaticMesh* LoadedMesh = nullptr;

};
