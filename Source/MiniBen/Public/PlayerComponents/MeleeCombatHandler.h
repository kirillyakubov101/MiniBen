// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/MeleeCombatInterface.h"
#include "MeleeCombatHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API UMeleeCombatHandler : public UActorComponent, public IMeleeCombatInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeCombatHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AssignNewWeapon_Implementation(UWeaponDataAsset* WeaponData);
	void AttackCommand_Implementation();
	void RotateCharacterToFaceForward_Implementation(float DeltaTime);

	void EndSingleTargetTrace_Implementation();
	void BeginSingleTargetTrace_Implementation();
	void ComboEnd_Implementation();
	void ComboNext_Implementation();

	void PlayAttackSequanceEvent();
	void TraceSingel();
	void LoadAttackAnimations(const TArray<TSoftObjectPtr<UAnimMontage>>& SoftListOfAnimations);
	void OnAttackAnimationsLoaded(TArray<TSoftObjectPtr<UAnimMontage>> SoftListOfAnimations);

	void ValidateStateContinue();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RotationTowardsCameraForwardSpeed = 10.f;

	int32 AmountOfAttacks;

	UPROPERTY()
	UWeaponDataAsset* CurrentWeapon;

	UPROPERTY(VisibleAnywhere)
	TArray<UAnimMontage*> ListOfAttacks;

	int32 CurrentAttackIndex = 0;
	bool bIsAttackMidway = false;
	bool bIsAttackQueued = false;
	float AttackCollisionSphere = 10.f;

	UPROPERTY()
	FTimerHandle AttackTraceTimer;

private:
	ECollisionChannel TraceChannel;

};
