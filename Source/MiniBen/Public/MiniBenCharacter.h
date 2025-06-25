// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MiniBenCharacter.generated.h"


UCLASS()
class MINIBEN_API AMiniBenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMiniBenCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
