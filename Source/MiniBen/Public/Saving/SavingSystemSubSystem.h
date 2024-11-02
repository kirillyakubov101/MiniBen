// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SavingSystemSubSystem.generated.h"

class USaveGameContainer;

UCLASS()
class MINIBEN_API USavingSystemSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString SlotName = "AutoSave";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USaveGameContainer* SaveGameContainer;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void SaveGame(const struct FMainSaveData& MainSaveData);

	UFUNCTION(BlueprintCallable)
	void InitSaveSlot();

	UFUNCTION(BlueprintCallable)
	USaveGameContainer* LoadGame();

	UFUNCTION(BlueprintCallable)
	USaveGameContainer* GetSaveData();
	
};
