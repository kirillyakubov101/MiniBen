// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestProgressWrapper.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MINIBEN_API UQuestProgressWrapper : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginDestroy() override;
	
};
