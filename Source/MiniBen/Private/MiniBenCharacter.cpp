// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenCharacter.h"

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

void AMiniBenCharacter::BindToRollEvent_Implementation(UObject* Object, FName FunctionName)
{
	if (Object && Object->IsValidLowLevel())
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(Object, FunctionName);
		OnRollDelegate.Add(Delegate);
	}
}


