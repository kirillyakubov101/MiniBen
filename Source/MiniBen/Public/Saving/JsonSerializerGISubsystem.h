// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "JsonSerializerGISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API UJsonSerializerGISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SerializeToJSON(const struct FMainSaveData& data);
	
};
