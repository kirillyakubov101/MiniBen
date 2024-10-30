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

	UFUNCTION()
	void OnLevelChanged(UWorld* LoadedWorld);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameModeIsReady();

	/// <summary>
	/// Saving Methods
	/// </summary>

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

	/// <summary>
	/// Loading Methods
	/// </summary>

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Load")
	void BeginLoadLevelProcess();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestorePlayer();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestoreCurrentWorldAssets();

	UFUNCTION(BlueprintCallable, Category = "Load")
	void RestoreSublevels();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
	FString CurrentLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	FMainSaveData MainSaveData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
	bool bHasGameInstanceStarted;

	UFUNCTION()
	void FinishStreamLevelsFunc();
	
};
