// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenPlayerController.h"
#include "GameEventsBroker.h"

void AMiniBenPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameEventsBroker::GetInst().BindToPlayerCanActivate(this, &AMiniBenPlayerController::OnPlayerLoaded);
}

void AMiniBenPlayerController::OnPlayerLoaded_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AMiniBenPlayerController player loaded"));
}

