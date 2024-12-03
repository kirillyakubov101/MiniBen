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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameModeIsReady();
	
	/// <summary>
	/// Saving Methods
	/// </summary>
	
	//Very important, it records all of the things we can save, it does NOT save it, just records it to the FMainSaveData struct of the game instance
	//It records on TWO occasions:
	//1. Load differnt level (we want to move to a new level with all of our things (don't save yet)
	//2. We click save, so it records all and then saves it
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Save")
	void RecordCurrentProgress(const FString& temp);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void InitCurrentWorld();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveSublevels();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SavePlayer(const FCharacterStats& PlayerStats);

	//UFUNCTION(BlueprintCallable, Category = "Save")
	//void SaveCurrentWorldAssets(); //this is actually calling all the actors that implement the ISaveable interface in the level

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem); //adds to the mainsavedata all the static items in the level (potions, collectables and more)

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddNPCToSaveData(const FSaveableWorldNpcs& newNpc); //adds to the mainsavedata all the Npcs that give quests and/or can be interacted with and change their state

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SavePlayerInventory(const TMap<FName, int32>& inventory);

	/// <summary>
	/// Loading Methods
	/// </summary>

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Load")
	void BeginLoadLevelProcess();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestorePlayer(FCharacterStats& PlayerStats,FVector& NewPos);

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestoreSublevels();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestorePlayerInventory(TMap<FName, int32>& Outinventory);

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestoreLoadedSublevelActors(TSoftObjectPtr<UWorld> LevelPtr);

	//returns a map of all the current world static/collectable items "FSaveableWorldItem" faster than just a list O(n) vs O(1)
	UFUNCTION(BlueprintPure, Category = "Load")
	const TMap<FGuid, FSaveableWorldItem> GetMapOfWorldItems() const;

	UFUNCTION(BlueprintPure, Category = "Load")
	const TMap<FGuid, FSaveableWorldNpcs> GetMapOfWorldNpcs() const;

	void ProcessNextSublevel();
	void RestoreSaveableActorsForAllSublevels(); //i need this only for the game load NOT the bridge levelstreaming
	

public:
	UPROPERTY(EditAnywhere,Category = "Save")
	TSubclassOf<class USaveGameContainer> SaveGameContainerClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
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

private:
	UFUNCTION()
	void FinishStreamLevelsFunc();
};
