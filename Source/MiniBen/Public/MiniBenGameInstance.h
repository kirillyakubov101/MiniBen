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

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveCurrentWorldAssets();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void AddNewWorldAssetToSaveData(const FSaveableWorldItem& newItem);

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
	void RestoreCurrentWorldAssets();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestoreSublevels();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestorePlayerInventory(TMap<FName, int32>& Outinventory);

	UFUNCTION(BlueprintPure, Category = "Load")
	TArray<FSaveableWorldItem> GetListOfWorldItems();

	void ProcessNextSublevel();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
	FString CurrentLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	FMainSaveData MainSaveData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
	bool bHasGameInstanceStarted;

private:
	// Struct to store information about each sublevel in the queue
	struct FQueuedSublevel
	{
		ULevelStreaming* Level;
		bool bShouldBeLoaded;
	};

private:
	TQueue<FQueuedSublevel> SublevelQueue;
	FCriticalSection LoadedComponentsMutex;


private:
	UFUNCTION()
	void FinishStreamLevelsFunc();
};
