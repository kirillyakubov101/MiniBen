// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenCharacter.h"
#include "MiniBenGameInstance.h"
#include "Camera/CameraComponent.h"
#include "GameEventsBroker.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerComponents/PlayerActorPermissionsHandler.h"
#include "PlayerComponents/LocomotionStateMachine.h"
#include "PlayerComponents/EquipmentHandler.h"
#include "PlayerComponents/MeleeCombatHandler.h"
#include "PlayerComponents/PlayerInventory.h"
#include "PlayerComponents/QuestManager.h"
#include "PlayerComponents/KillsHandler.h"
#include "PlayerComponents//PlayerHealth.h"
#include "PlayerComponents/AbilityHandler.h"
#include "Data/WeaponDataAsset.h"
#include "Components/AudioComponent.h"
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

	//KillsHandleer
	KillsHandler = CreateDefaultSubobject<UKillsHandler>(TEXT("KillsHandler"));

	//AbilityHandler
	AbilityHandler = CreateDefaultSubobject<UAbilityHandler>(TEXT("AbilityHandler"));

	//Audio Component - Bow
	BowAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BowAudioComponent"));
	BowAudioComponent->SetupAttachment(RootComponent);
	PlayerAudioMap.Add("Bow", BowAudioComponent);
}


void AMiniBenCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UMiniBenGameInstance>(GetGameInstance());
	check(GameInstance);

	GetAndAssignPlayerComponents();

	//Subscribe
	GameEventsBroker::GetInst().BindToPlayerCanActivate(this, &AMiniBenCharacter::HandlePlayerActivated);
	GameEventsBroker::GetInst().BindToPlayerDeath(this, &AMiniBenCharacter::HandlePlayerDeath);
}

void AMiniBenCharacter::GetAndAssignPlayerComponents()
{
	for (auto* Component : GetComponents())
	{
		// Check if component implements PlayerHealthInterface
		if (Component->Implements<UPlayerHealthInterface>())
		{
			PlayerHealth = Cast<UPlayerHealth>(Component);
			continue;  // optional if you only want one component per interface
		}

		// Check if component implements PlayerInventoryInterface
		if (Component->Implements<UPlayerInventoryInterface>())
		{
			PlayerInventory = Cast<UPlayerInventory>(Component);
			continue;
		}

		// Check if component implements QuestManagerInterface
		if (Component->Implements<UQuestManagerInterface>())
		{
			QuestManager = Cast<UQuestManager>(Component);
			continue;
		}
	}

		////PlayerHealth
		//auto PlayerHealthComponents = GetComponentsByInterface(UPlayerHealthInterface::StaticClass());
		//if (PlayerHealthComponents.Num() > 0)
		//{
		//	PlayerHealth = Cast<UPlayerHealth>(PlayerHealthComponents[0]);
		//}

		////PlayerInventory
		//auto PlayerInventoryComponent = GetComponentsByInterface(UPlayerInventoryInterface::StaticClass());
		//if (PlayerInventoryComponent.Num() > 0)
		//{
		//	PlayerInventory = Cast<UPlayerInventory>(PlayerInventoryComponent[0]);
		//}

		////QuestManager
		//auto PlayerQuestComponent = GetComponentsByInterface(UQuestManagerInterface::StaticClass());
		//if (PlayerQuestComponent.Num() > 0)
		//{
		//	QuestManager = Cast<UQuestManager>(PlayerQuestComponent[0]);
		//}
}


void AMiniBenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMiniBenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMiniBenCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GameEventsBroker::GetInst().UnBindPlayerCanActivate(this);
	GameEventsBroker::GetInst().UnBindPlayerDeath(this);
	UE_LOG(LogTemp, Warning, TEXT("REMOVING PLAYER VIA ENDPLAY"));
}

void AMiniBenCharacter::SavePlayerInventory(const TMap<FName, int32>& inventory)
{
	GameInstance->SavePlayerInventory(inventory);
}

void AMiniBenCharacter::RestorePlayerInventory(TMap<FName, int32>& Outinventory)
{
	Outinventory = GameInstance->GetPlayerInventory();
}

void AMiniBenCharacter::SaveAndRecordSelf_Implementation()
{
	FPlayerTransformData PlayerTransformData(GetActorTransform());
	GameInstance->SavePlayerTransform(PlayerTransformData);
	GameInstance->SavePlayerAbilities(AbilityHandler->Abilities);
	ISaveable::Execute_SaveAndRecordSelf(this->QuestManager);
}

void AMiniBenCharacter::LoadAndRestoreSelf_Implementation()
{
	SetActorTransform(GameInstance->GetPlayerTransformData().PlayerTransform);
	AbilityHandler->Abilities = GameInstance->GetPlayerAbilities();
	ISaveable::Execute_LoadAndRestoreSelf(this->QuestManager);
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

TScriptInterface<class IPlayerHealthInterface> AMiniBenCharacter::GetPlayerHealthHandler_Implementation()
{
	return PlayerHealth;
}

TScriptInterface<class IPlayerHealthInterface> AMiniBenCharacter::GetPlayerHealthHandlerNative()
{
	return PlayerHealth;
}

TScriptInterface<class IKillHandlerInterface> AMiniBenCharacter::GetKillsHandler_Implementation()
{
	return KillsHandler;
}

TScriptInterface<class IKillHandlerInterface> AMiniBenCharacter::GetKillsHandlerNative()
{
	return KillsHandler;
}

TScriptInterface<class IQuestManagerInterface> AMiniBenCharacter::GetQuestManager_Implementation()
{
	return QuestManager;
}

TScriptInterface<class IQuestManagerInterface> AMiniBenCharacter::GetQuestManagerNative()
{
	return QuestManager;
}

TScriptInterface<class IPlayerInventoryInterface> AMiniBenCharacter::GetPlayerInventory_Implementation()
{
	return PlayerInventory;
}

TScriptInterface<class IPlayerInventoryInterface> AMiniBenCharacter::GetPlayerInventoryNative()
{
	return PlayerInventory;
}

void AMiniBenCharacter::SetCharMoveSpeed_Implementation(EPlayerMovementState NewMovementState)
{
	switch (NewMovementState)
	{
	case EPlayerMovementState::MS_Normal:
		PlayerMaxWalkSpeed = 500.f;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	case EPlayerMovementState::MS_FistCombat:
		PlayerMaxWalkSpeed = 120.f;
		break;
	case EPlayerMovementState::MS_OneHandedSwordCombat:
		PlayerMaxWalkSpeed = 320.f;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		break;
	case EPlayerMovementState::MS_Locked:
		PlayerMaxWalkSpeed = 0.f;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	case EPlayerMovementState::MS_RangedCombat:
		PlayerMaxWalkSpeed = 300.f;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		break;

	default:
		PlayerMaxWalkSpeed = 0.f;
	
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

TScriptInterface<IState> AMiniBenCharacter::GetRangedCombatState_Implementation() const
{
	return TScriptInterface<IState>();
}

EWeaponType AMiniBenCharacter::GetWeaponTypeBasedOnCombatState_Implementation() const
{
	return EWeaponType();
}

TScriptInterface<IState> AMiniBenCharacter::GetOneHandedCombatState() const
{
	return TScriptInterface<IState>();
}

TScriptInterface<IState> AMiniBenCharacter::GetFistCombatState_Implementation() const
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

UStaticMeshComponent* AMiniBenCharacter::GetBackWeaponStaticMeshComp_Implementation() const
{
	return nullptr;
}

void AMiniBenCharacter::NotifyForNewReadyMeleeWeapon_Implementation(UWeaponDataAsset* NewWeapon)
{
	IMeleeCombatInterface::Execute_AssignNewWeapon(this->MeleeCombatHandler, NewWeapon);
}

void AMiniBenCharacter::NotifyForNewReadyRangedWeapon_Implementation(UWeaponDataAsset* NewWeapon)
{
	// TODO: Implement Ranged Combat Handler and call its AssignNewWeapon method here
	/*IMeleeCombatInterface::Execute_AssignNewWeapon(this->Ranged, NewWeapon);*/
}

void AMiniBenCharacter::TakeDamageNative(AActor* Inst, float DamageAmount, FVector HitLocation)
{
	//
}

UAudioComponent* AMiniBenCharacter::GetAudioComponentByName_Implementation(FName ComponentName) const
{
	auto Found = PlayerAudioMap.Find(ComponentName);
	if (Found)
	{
		return *Found;
	}
		
	return nullptr;
}

void AMiniBenCharacter::HandlePlayerActivated()
{
	UE_LOG(LogTemp, Warning, TEXT("HandlePlayerActivated was called by broker"));
	ISaveable::Execute_LoadAndRestoreSelf(this);
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




