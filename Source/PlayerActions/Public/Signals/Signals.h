// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Signals.generated.h"

USTRUCT(BlueprintType)
struct FBaseSignal {
	GENERATED_BODY()

	FBaseSignal(){}
	virtual ~FBaseSignal() {}
};

USTRUCT(BlueprintType)
struct FCollectQuestSignal:public FBaseSignal {

	GENERATED_BODY()

public:
	FCollectQuestSignal() {

	}

	FString QuestName;
	int32 AmountToCollect;
	FString ItemToCollect;

};