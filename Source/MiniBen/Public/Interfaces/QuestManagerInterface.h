// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UQuestManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIBEN_API IQuestManagerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "QuestManager")
	void AddNewQuestWithId(FName QuestId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "QuestManager")
	void CompleteQuestWithId(FName QuestId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "QuestManager")
	void TrackKilledEnemyByClass(TSubclassOf<class AGameEntity_Enemy> EnemyClass);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "QuestManager")
	void TrackCollectedItemByClass(TSubclassOf<class AItem> ItemClass);
};
