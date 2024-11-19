// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "JsonSerializerGISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API UJsonSerializerGISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SerializeToJSON(const struct FMainSaveData& data);

protected:
	TSharedPtr<FJsonObject> SerializeCharacterStats(const struct FCharacterStats& Stats);
	TSharedPtr<FJsonObject> SerializeSaveableWorldItem(const struct FSaveableWorldItem& Item);
	TSharedPtr<FJsonObject> SerializeWorldDataSave(const struct FWorldDataSave& WorldData);
	TSharedPtr<FJsonObject> SerializePlayerInventory(const TMap<FName, int32>& WorldData);
	
private:
	FString FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Saved/SaveGames/MyStructData.json"));
};
