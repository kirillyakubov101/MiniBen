// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../PlayerActions/Public/Saveable.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/PlayerComponentBroker.h"
#include "Interfaces/PlayerActionPermissions.h"
#include "Interfaces/CharacterMovementInterface.h"
#include "Interfaces/CombatStateInterface.h"
#include "Interfaces/CharacterMeshInterface.h"
#include "Interfaces/EquipmentInterface.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/LocomotionStateMachineInterface.h"
#include "Interfaces/EquipHelperInterface.h"
#include "Interfaces/PlayerSoundHandlerInterface.h"
#include "Interfaces/CameraHandlerInterface.h"	
#include "MiniBenCharacter.generated.h"

class UWeaponDataAsset;
class UAudioComponent;

UCLASS()
class MINIBEN_API AMiniBenCharacter :
	public ACharacter,
	public ISaveable,
	public IPlayerInterface,
	public IPlayerComponentBrokerInterface,
	public ICharacterMovementInterface,
	public ICombatStateInterface,
	public ICharacterMeshInterface,
	public ICombatInterface,
	public IDamageable,
	public IEquipHelperInterface,
	public IPlayerSoundHandlerInterface,
	public ICameraHandlerInterface
{
	GENERATED_BODY()

public:
	AMiniBenCharacter();

protected:
	virtual void BeginPlay() override;

	void GetAndAssignPlayerComponents();


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void SavePlayerInventory(const TMap<FName, int32>& inventory);

	UFUNCTION(BlueprintCallable)
	void RestorePlayerInventory(TMap<FName, int32>& Outinventory);

	UFUNCTION(BlueprintImplementableEvent)
	void HandlePlayerDeath();

	// ISaveable Interface
	virtual void SaveAndRecordSelf_Implementation() override;
	virtual void LoadAndRestoreSelf_Implementation() override;

	// IPlayerInterface Interface
	virtual bool CanBeTargeted_Implementation() override;

	// IPlayerComponentBrokerInterface Interface
	virtual FVector GetPlayerCameraForward_Implementation() const override;
	virtual TScriptInterface<class IPlayerActionPermissions> GetPlayerActionPermissions_Implementation() override;
	virtual IPlayerActionPermissions* GetPlayerActionPermissionsNative() override;
	virtual TScriptInterface<class IEquipmentInterface> GetEquipmentHandler();
	virtual IEquipmentInterface* GetEquipmentHandlerNative() override;
	virtual TScriptInterface<class IMeleeCombatInterface> GetMeleeCombatHandler_Implementation() override;
	virtual class IMeleeCombatInterface* GetMeleeCombatHandlerNative() override;
	virtual TScriptInterface<class ILocomotionStateMachineInterface> GetStateMachine_Implementation() override;
	virtual TScriptInterface<class ILocomotionStateMachineInterface> GetStateMachineNative() override;
	virtual TScriptInterface<class IPlayerHealthInterface> GetPlayerHealthHandler_Implementation() override;
	virtual class TScriptInterface<class IPlayerHealthInterface> GetPlayerHealthHandlerNative() override;
	virtual TScriptInterface<class IKillHandlerInterface> GetKillsHandler_Implementation() override;
	virtual class TScriptInterface<class IKillHandlerInterface> GetKillsHandlerNative() override;
	virtual TScriptInterface<class IQuestManagerInterface> GetQuestManager_Implementation() override;
	virtual class TScriptInterface<class IQuestManagerInterface> GetQuestManagerNative() override;
	virtual TScriptInterface<class IPlayerInventoryInterface> GetPlayerInventory_Implementation() override;
	virtual class TScriptInterface<class IPlayerInventoryInterface> GetPlayerInventoryNative() override;

	// ICharacterMovementInterface
	virtual void SetCharMoveSpeed_Implementation(EPlayerMovementState NewMovementState) override;
	virtual EPlayerMovementState GetCurrentLocomotionState_Implementation() const;
	virtual void ToggleMovement_Implementation(bool bCanMove);

	// ICombatStateInterface
	virtual EWeaponType GetWeaponTypeBasedOnCombatState_Implementation() const;
	virtual TScriptInterface<IState> GetOneHandedCombatState() const;
	virtual TScriptInterface<IState> GetFistCombatState_Implementation() const;
	virtual TScriptInterface<IState> GetNormalState_Implementation() const override;
	virtual TScriptInterface<IState> GetRangedCombatState_Implementation() const override;

	// ICharacterMeshInterface
	virtual USkeletalMeshComponent* GetCharacterSkeletalMesh_Implementation() const;
	virtual UStaticMeshComponent* GetLeftWeaponHolsterStaticMeshComp_Implementation() const;
	virtual UStaticMeshComponent* GetBackWeaponStaticMeshComp_Implementation() const;

	// ICombatInterface
	virtual UWeaponDataAsset* GetCurrentWeapon_Implementation() const override;
	virtual void NotifyForNewReadyMeleeWeapon_Implementation(UWeaponDataAsset* NewWeapon) override;
	virtual void NotifyForNewReadyRangedWeapon_Implementation(UWeaponDataAsset* NewWeapon) override;
	
	// IDamageable
	virtual void TakeDamageNative(AActor* Instigator, float DamageAmount, FVector HitLocation) override;

	// IEquipHelperInterface - Done in BP

	// IPlayerSoundHandlerInterface
	virtual UAudioComponent* GetAudioComponentByName_Implementation(FName ComponentName) const override;

	// ICameraHandlerInterface
	virtual class USpringArmComponent* GetCameraBoom_Implementation() const;
	virtual class UCameraComponent* GetMainCamera_Implementation() const;

protected:
	void HandlePlayerActivated();

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
	class ULocomotionStateMachine* LocomotionStateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMeleeCombatHandler* MeleeCombatHandler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UKillsHandler* KillsHandler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPlayerHealth* PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPlayerInventory* PlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UQuestManager* QuestManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAbilityHandler* AbilityHandler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAudioComponent* BowAudioComponent;
		
	
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
	TMap<FName, UAudioComponent*> PlayerAudioMap;
};
