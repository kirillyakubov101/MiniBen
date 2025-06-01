// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniBenGameMode.h"
#include "MiniBenGameInstance.h"

void AMiniBenGameMode::BeginPlay()
{
	Super::BeginPlay();
	//DEPRECATED
	/*UMiniBenGameInstance* MiniBenGameInstance = Cast<UMiniBenGameInstance>(GetGameInstance());
	if (MiniBenGameInstance)
	{
		MiniBenGameInstance->GameModeIsReady();
	}*/
}

