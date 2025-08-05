// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenCharacter.h"
#include "MiniBenGameInstance.h"
#include "Camera/CameraComponent.h"
#include "GameEventsBroker.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerComponents/PlayerActorPermissionsHandler.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerComponents/LocomotionStateMachine.h"
#include "PlayerComponents/EquipmentHandler.h"
#include "PlayerComponents/MeleeCombatHandler.h"
#include "Data/WeaponDataAsset.h"
#include "MyStructs.h"

// Sets default values
AMiniBenCharacter::AMiniBenCharacter()
	:PlayerMovementState(EPlayerMovementState::MS_Normal), bCanPlayerMove(true)
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Components
	PlayerActorPermissionsHandler = CreateDefaultSubobject<UPlayerActorPermissionsHandler>(TEXT("PlayerPermissionsHandler"));

	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	MainCameraComponent->SetupAttachment(CameraBoom);

	//Locomotion
	LocomotionStateMachine = CreateDefaultSubobject<ULocomotionStateMachine>(TEXT("LocomotionStateMachine"));

	//EquipmentHandler
	EquipmentHandler = CreateDefaultSubobject<UEquipmentHandler>(TEXT("EquipmentHandler"));

	//MeleeCombatHandler
	MeleeCombatHandler = CreateDefaultSubobject<UMeleeCombatHandler>(TEXT("MeleeCombatHandler"));
}


void AMiniBenCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UMiniBenGameInstance>(GetGameInstance());
	check(GameInstance);
	

	//Subscribe
	GameEventsBroker::GetInst().BindToPlayerCanActivate(this, &AMiniBenCharacter::LoadAndRestoreSelf_Implementation);
	GameEventsBroker::GetInst().BindToPlayerDeath(this, &AMiniBenCharacter::HandlePlayerDeath);
}


void AMiniBenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMiniBenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMiniBenCharacter::SavePlayerInventory(const TMap<FName, int32>& inventory)
{
	GameInstance->GetPlayerInventory() = inventory;
}

void AMiniBenCharacter::RestorePlayerInventory(TMap<FName, int32>& Outinventory)
{
	Outinventory = GameInstance->GetPlayerInventory();
}

void AMiniBenCharacter::SaveAndRecordSelf_Implementation()
{
	GameInstance->GetWorldDataSave()->PlayerTransformData.PlayerTransform = GetActorTransform();
	//inventory and quests should be saved here as well
}

void AMiniBenCharacter::LoadAndRestoreSelf_Implementation()
{
	SetActorTransform(GameInstance->GetWorldDataSave()->PlayerTransformData.PlayerTransform);
	ISaveable::Execute_LoadAndRestoreSelf(this);
	//inventory and quests should be loaded here as well
}

void AMiniBenCharacter::SignalEnemyKilled_Implementation(TSubclassOf<class AGameEntity_Enemy> EnemyClass)
{
	//
}

bool AMiniBenCharacter::CanBeTargeted_Implementation()
{
	return bCanPlayerBeTargeted;
}


FVector AMiniBenCharacter::GetPlayerCameraForward_Implementation() const
{
	if (MainCameraComponent)
	{
		return MainCameraComponent->GetForwardVector();
	}

	// Fallback if camera not found
	return FVector::ForwardVector;
}

TScriptInterface<IPlayerActionPermissions> AMiniBenCharacter::GetPlayerActionPermissions_Implementation()
{
	TScriptInterface<IPlayerActionPermissions> OutInterface;
	OutInterface.SetObject(PlayerActorPermissionsHandler);
	OutInterface.SetInterface(Cast<IPlayerActionPermissions>(PlayerActorPermissionsHandler));
	return OutInterface;
}

IPlayerActionPermissions* AMiniBenCharacter::GetPlayerActionPermissionsNative()
{
	IPlayerActionPermissions* InterfacePtr = Cast<IPlayerActionPermissions>(PlayerActorPermissionsHandler);
	if (!InterfacePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerActorPermissionsHandler on %s does not implement IPlayerActionPermissions!"), *GetName());
		return nullptr;
	}

	return InterfacePtr;
}

TScriptInterface<class IEquipmentInterface> AMiniBenCharacter::GetEquipmentHandler()
{
	return TScriptInterface<class IEquipmentInterface>();
}

IEquipmentInterface* AMiniBenCharacter::GetEquipmentHandlerNative()
{
	IEquipmentInterface* InterfacePtr = Cast<IEquipmentInterface>(EquipmentHandler);
	if (!InterfacePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("EquipmentHandler on %s does not implement IEquipmentInterface!"), *GetName());
		return nullptr;
	}

	return InterfacePtr;
}

TScriptInterface<class IMeleeCombatInterface> AMiniBenCharacter::GetMeleeCombatHandler_Implementation()
{
	return MeleeCombatHandler;
}

IMeleeCombatInterface* AMiniBenCharacter::GetMeleeCombatHandlerNative()
{
	IMeleeCombatInterface* InterfacePtr = Cast<IMeleeCombatInterface>(MeleeCombatHandler);
	if (!InterfacePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("MeleeCombatHandler on %s does not implement IMeleeCombatInterface!"), *GetName());
		return nullptr;
	}

	return InterfacePtr;
}

TScriptInterface<ILocomotionStateMachineInterface> AMiniBenCharacter::GetStateMachine_Implementation()
{
	return LocomotionStateMachine;
}

TScriptInterface<ILocomotionStateMachineInterface> AMiniBenCharacter::GetStateMachineNative()
{
	return LocomotionStateMachine;
}

void AMiniBenCharacter::SetCharMoveSpeed_Implementation(EPlayerMovementState NewMovementState)
{
	switch (NewMovementState)
	{
	case EPlayerMovementState::MS_Normal:
		PlayerMaxWalkSpeed = 500.f;
		break;
	case EPlayerMovementState::MS_FistCombat:
		PlayerMaxWalkSpeed = 120.f;
		break;
	case EPlayerMovementState::MS_OneHandedSwordCombat:
		PlayerMaxWalkSpeed = 320.f;
		break;
	case EPlayerMovementState::MS_Locked:
		PlayerMaxWalkSpeed = 0.f;
		break;
	}

	GetCharacterMovement()->MaxWalkSpeed = PlayerMaxWalkSpeed;
}

EPlayerMovementState AMiniBenCharacter::GetCurrentLocomotionState_Implementation() const
{
	return PlayerMovementState;
}

void AMiniBenCharacter::ToggleMovement_Implementation(bool bCanMove)
{
	this->bCanPlayerMove = bCanMove;
}


TScriptInterface<IState> AMiniBenCharacter::GetNormalState_Implementation() const
{
	return TScriptInterface<IState>();
}

EWeaponType AMiniBenCharacter::GetWeaponTypeBasedOnCombatState() const
{
	return EWeaponType();
}

TScriptInterface<IState> AMiniBenCharacter::GetOneHandedCombatState() const
{
	return TScriptInterface<IState>();
}

TScriptInterface<IState> AMiniBenCharacter::GetFistCombatState() const
{
	return TScriptInterface<IState>();
}

USkeletalMeshComponent* AMiniBenCharacter::GetCharacterSkeletalMesh_Implementation() const
{
	return nullptr;
}

UStaticMeshComponent* AMiniBenCharacter::GetLeftWeaponHolsterStaticMeshComp_Implementation() const
{
	return nullptr;
}


FTransform AMiniBenCharacter::GetRightHandTransform_Implementation() const
{
	return FTransform();
}

void AMiniBenCharacter::NotifyForNewReadyWeapon_Implementation(UWeaponDataAsset* NewWeapon)
{
	IMeleeCombatInterface::Execute_AssignNewWeapon(this->MeleeCombatHandler, NewWeapon);
}

UWeaponDataAsset* AMiniBenCharacter::GetCurrentWeapon_Implementation() const
{
	if (this->EquipmentHandler->GetClass()->ImplementsInterface(UEquipmentInterface::StaticClass()))
	{
		return IEquipmentInterface::Execute_GetCurrentWeapon(this->EquipmentHandler);
	}
	UE_LOG(LogTemp, Error, TEXT("GetCurrentWeapon_Implementation -> error EquipmentHandler" ));
	return nullptr;
}




