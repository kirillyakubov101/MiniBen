// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenCharacter.h"
#include "MiniBenGameInstance.h"

// Sets default values
AMiniBenCharacter::AMiniBenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMiniBenCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UMiniBenGameInstance>(GetGameInstance());
	check(GameInstance);
}

// Called every frame
void AMiniBenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
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
	//inventory and quests should be loaded here as well
}




