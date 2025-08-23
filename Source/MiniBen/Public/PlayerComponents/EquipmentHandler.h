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
	virtual void EquipWeapon_Implementation(UWeaponDataAsset* NewWeapon) override;
	virtual UStaticMesh* GetCurrentWeaponMesh_Implementation() const override;
	virtual bool IsWeaponReady_Implementation() const;
	virtual void ReadyWeapon_Implementation();
	virtual void LowerWeapon_Implementation();
	virtual EWeaponType GetCurrentlyEquippedWeaponType_Implementation() const override;
	virtual UWeaponDataAsset* GetCurrentWeapon_Implementation() const override;
	virtual void UnequipWeapon_Implementation() override;
	virtual bool IsNoWeaponAssigned_Implementation() const override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsWeaponSheathed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWeaponDataAsset* CurrentWeapon;

private:
	class TScriptInterface<class ILocomotionStateMachineInterface> LocomotionStateMachine;

	UPROPERTY()
	UStaticMesh* LoadedMesh = nullptr;

	TWeakObjectPtr<UStaticMeshComponent> InactiveStaticMeshComp;

};
