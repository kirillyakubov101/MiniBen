// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/QuestManagerInterface.h"
#include "Saveable.h"
#include "QuestManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API UQuestManager : public UActorComponent, public IQuestManagerInterface, public ISaveable
{
	GENERATED_BODY()

public:	
	UQuestManager();

protected:
	virtual void BeginPlay() override;

	// ISaveable Interface
	virtual void SaveAndRecordSelf_Implementation() override;
	virtual void LoadAndRestoreSelf_Implementation() override;

public:	
	virtual void AddNewQuestWithId_Implementation(FName QuestId) override;
	virtual void CompleteQuestWithId_Implementation(FName QuestId) override;
	virtual void TrackKilledEnemyByClass_Implementation(TSubclassOf<class AGameEntity_Enemy> EnemyClass) override;
	virtual void TrackCollectedItemByClass_Implementation(TSubclassOf<class AItem> ItemClass) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", SaveGame)
	TArray<FName> ListOfActiveQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", SaveGame)
	TArray<FName> ListOfPendingCompletedQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", SaveGame)
	TArray<FName> ListOfCompletedQuests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", SaveGame)
	TMap<FName, class UQuestProgressWrapper*> MapOfProgress;

private:
	void HandleEnemyKilled(TSubclassOf<class AGameEntity_Enemy> EnemyClass);
	class UMiniBenGameInstance* GameInstance;
};
