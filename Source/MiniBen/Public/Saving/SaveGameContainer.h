// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyStructs.h"
#include "SaveGameContainer.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API USaveGameContainer : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Saving", SaveGame)
	FMainSaveData MainSaveData;
	
};
