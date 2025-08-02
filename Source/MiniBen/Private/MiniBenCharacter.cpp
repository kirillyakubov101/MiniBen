// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenCharacter.h"
#include "MiniBenGameInstance.h"
#include "Camera/CameraComponent.h"
#include "GameEventsBroker.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerComponents/PlayerActorPermissionsHandler.h"

// Sets default values
AMiniBenCharacter::AMiniBenCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Components
	PlayerActorPermissionsHandler = CreateDefaultSubobject<UPlayerActorPermissionsHandler>(TEXT("PlayerPermissionsHandler"));
	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	MainCameraComponent->SetupAttachment(CameraBoom);
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




