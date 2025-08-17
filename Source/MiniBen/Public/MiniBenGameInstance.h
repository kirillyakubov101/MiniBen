// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStructs.h"
#include "Engine/GameInstance.h"
#include "MiniBenGameInstance.generated.h"





UCLASS()
class MINIBEN_API UMiniBenGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Save")
	void OnLevelChanged(UWorld* LoadedWorld);

	/// <summary>
	/// Saving Methods
	/// </summary>
	
	//Very important, it records all of the things we can save, it does NOT save it, just records it to the FMainSaveData struct of the game instance
	//It records on TWO occasions:
	//1. Load differnt level (we want to move to a new level with all of our things (don't save yet)
	//2. We click save, so it records all and then saves it
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Save")
	void RecordCurrentProgress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save")
	void PreLoadMapEvent(const FString& temp);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void InitCurrentWorld();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveSublevels();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SavePlayer();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem); //adds to the mainsavedata all the static items in the level (potions, collectables and more)

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddNPCToSaveData(const FSaveableWorldNpcs& newNpc); //adds to the mainsavedata all the Npcs that give quests and/or can be interacted with and change their state

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddEnemyToSaveData(const FSavealbeWorldEnemy& newEnemy);


	/// <summary>
	/// Loading Methods
	/// </summary>

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Load")
	void BeginLoadLevelProcess();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestoreSublevels();

	//returns a map of all the current world static/collectable items "FSaveableWorldItem" faster than just a list O(n) vs O(1)
	UFUNCTION(BlueprintPure, Category = "Load")
	const TMap<FGuid, FSaveableWorldItem> GetMapOfWorldItems() const;

	UFUNCTION(BlueprintPure, Category = "Load")
	const TMap<FGuid, FSaveableWorldNpcs> GetMapOfWorldNpcs() const;

	UFUNCTION(BlueprintPure, Category = "Load")
	const TMap<FGuid, FSavealbeWorldEnemy> GetMapOfWorldEnemies() const;

	void ProcessNextSublevel();
	void NotifyPlayerToSelfRestore();
	

public:
	UPROPERTY(EditAnywhere,Category = "Save")
	TSubclassOf<class USaveGameContainer> SaveGameContainerClass;

public:
	//Getters
	const FPlayerTransformData& GetPlayerTransformData() const { return this->CurrentWorldDataSave->PlayerTransformData; }
	const TMap<FName, int32>& GetPlayerInventory() const { return this->MainSaveData.PlayerInventory; }
	const FGlobalQuestData& GetGlobalQuestData() const { return this->MainSaveData.GlobalQuestData; }
	const TMap<FGameplayTag, bool>& GetPlayerAbilities() const { return this->MainSaveData.PlayerAbilities; }
	const TMap<FName, FActiveQuestProgress>& GetActiveQuestProgress() const { return this->MainSaveData.ActiveQuestsProgress; }

	//Setters
	void SetGlobalQuestData(const FGlobalQuestData& GlobalQuestData);
	void SavePlayerInventory(const TMap<FName,int32>& inventory);
	void SavePlayerTransform(const FPlayerTransformData& PlayerTransformData);
	void SavePlayerAbilities(const TMap<FGameplayTag, bool>& PlayerAbilities);
	void SaveQuestsProgress(const TMap<FName,FActiveQuestProgress>& Progress);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	FString CurrentLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	FMainSaveData MainSaveData;

private:
	// Struct to store information about each sublevel in the queue
	struct FQueuedSublevel
	{
		ULevelStreaming* Level;
		bool bShouldBeLoaded;
	};

private:
	TQueue<FQueuedSublevel> SublevelQueue;
	FWorldDataSave* CurrentWorldDataSave = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true),Category = "Save")
	FName IntroLevelName = "Intro_Level";

	void SetCurrentWorldDataSave();

private:
	UFUNCTION()
	void FinishStreamLevelsFunc();
	UFUNCTION(BlueprintPure, Category = "Save")
	bool IsCurrentLevelGameLevel() const;

	

	//void RestoreSaveableActorsForAllSublevels(); //DEPRECATED
};
