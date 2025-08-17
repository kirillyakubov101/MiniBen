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
	void InitStartValuesOfQuestProgressWrapper(FName CurrentQuestId, UClass* TargetClass, int32 CurrentAmount, int32 Requirement, UClass* WrapperClass = nullptr);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FName CurrentQuestId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UClass* TargetClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 CurrentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 Requirement;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void InitializeProgressWrapper();
	
};
