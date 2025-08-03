// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../PlayerActions/Public/Saveable.h"
#include "Interfaces/KillHandlerInterface.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/PlayerComponentBroker.h"
#include "Interfaces/PlayerActionPermissions.h"
#include "Interfaces/CharacterMovementInterface.h"
#include "Interfaces/StateMachineInterface.h"
#include "Interfaces/CombatStateInterface.h"
#include "Interfaces/CharacterMeshInterface.h"
#include "Interfaces/EquipmentInterface.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/LocomotionStateMachineInterface.h"
#include "MiniBenCharacter.generated.h"

class UWeaponDataAsset;

UCLASS()
class MINIBEN_API AMiniBenCharacter :
	public ACharacter,
	public ISaveable,
	public IKillHandlerInterface,
	public IPlayerInterface,
	public IPlayerComponentBrokerInterface,
	public ICharacterMovementInterface,
	public IStateMachineInterface,
	public ICombatStateInterface,
	public ICharacterMeshInterface,
	public ICombatInterface
{
	GENERATED_BODY()

public:
	AMiniBenCharacter();

protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SavePlayerInventory(const TMap<FName, int32>& inventory);

	UFUNCTION(BlueprintCallable)
	void RestorePlayerInventory(TMap<FName, int32>& Outinventory);

	UFUNCTION(BlueprintImplementableEvent)
	void HandlePlayerDeath();

	// ISaveable Interface
	virtual void SaveAndRecordSelf_Implementation();
	virtual void LoadAndRestoreSelf_Implementation();

	// IKillHandlerInterface Interface
	virtual void SignalEnemyKilled_Implementation(TSubclassOf<class AGameEntity_Enemy> EnemyClass);

	// IPlayerInterface Interface
	virtual bool CanBeTargeted_Implementation();

	// IPlayerComponentBrokerInterface Interface
	virtual FVector GetPlayerCameraForward_Implementation() const;
	virtual TScriptInterface<class IPlayerActionPermissions> GetPlayerActionPermissions_Implementation();
	virtual IPlayerActionPermissions* GetPlayerActionPermissionsNative() override;
	virtual IEquipmentInterface* GetEquipmentHandlerNative() override;
	virtual TScriptInterface<class IMeleeCombatInterface> GetMeleeCombatHandler_Implementation();
	virtual class IMeleeCombatInterface* GetMeleeCombatHandlerNative() override;

	// ICharacterMovementInterface
	void SetCharMoveSpeed_Implementation(EPlayerMovementState NewMovementState);
	EPlayerMovementState GetCurrentLocomotionState_Implementation() const;
	void ToggleMovement_Implementation(bool bCanMove);

	// IStateMachineInterface
	TScriptInterface<ILocomotionStateMachineInterface> GetStateMachine_Implementation() const;

	// ICombatStateInterface
	EWeaponType GetWeaponTypeBasedOnCombatState() const;
	TScriptInterface<IState> GetOneHandedCombatState() const;
	TScriptInterface<IState> GetFistCombatState() const;
	TScriptInterface<IState> GetNormalState_Implementation() const;

	// ICharacterMeshInterface
	USkeletalMeshComponent* GetCharacterSkeletalMesh_Implementation() const;
	UStaticMeshComponent* GetLeftWeaponHolsterStaticMeshComp_Implementation() const;

	// ICombatInterface
	UWeaponDataAsset* GetCurrentWeapon_Implementation() const;
	FTransform GetRightHandTransform_Implementation() const;
	void NotifyForNewReadyWeapon_Implementation(UWeaponDataAsset* NewWeapon);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanPlayerBeTargeted;

	//==============================Components=================================//
	//--------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* MainCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPlayerActorPermissionsHandler* PlayerActorPermissionsHandler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UEquipmentHandler* EquipmentHandler;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ULocomotionStateMachine* LocomotionStateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMeleeCombatHandler* MeleeCombatHandler;

	//-----------------------------------------------------------------------//
	//======================================================================//

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterMovementInterface")
	bool bCanPlayerMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterMovementInterface")
	EPlayerMovementState PlayerMovementState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterMovementInterface")
	float PlayerMaxWalkSpeed = 500.f;



private:
	class UMiniBenGameInstance* GameInstance;	
};
