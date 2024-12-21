// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStructs.h"
#include "GameFramework/GameModeBase.h"
#include "MiniBenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AMiniBenGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
};
