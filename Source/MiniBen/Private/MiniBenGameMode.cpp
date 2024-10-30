// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenGameMode.h"
#include "MiniBenGameInstance.h"

void AMiniBenGameMode::AssignSaveData(const FMainSaveData& data)
{
	this->MainSaveDataDev = data;
}

void AMiniBenGameMode::BeginPlay()
{
	Super::BeginPlay();

	UMiniBenGameInstance* MiniBenGameInstance = Cast<UMiniBenGameInstance>(GetGameInstance());
	if (MiniBenGameInstance)
	{
		MiniBenGameInstance->GameModeIsReady();
	}
}

