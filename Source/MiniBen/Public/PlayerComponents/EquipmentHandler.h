// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <MyStructs.h>
#include "EquipmentHandler.generated.h"


class UWeaponDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API UEquipmentHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentHandler();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(UWeaponDataAsset* NewWeapon);

	UFUNCTION(BlueprintPure)
	UStaticMesh* GetCurrentWeaponMesh() const;

	UFUNCTION(BlueprintPure)
	bool IsWeaponReady() const;

	UFUNCTION(BlueprintCallable)
	void ReadyWeapon();

	UFUNCTION(BlueprintCallable)
	void LowerWeapon();

	UFUNCTION(BlueprintPure)
	EWeaponType GetCurrentlyEquippedWeaponType() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsWeaponSheathed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWeaponDataAsset* CurrentWeapon;

};
