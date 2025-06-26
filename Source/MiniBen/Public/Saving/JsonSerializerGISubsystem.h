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
	void SerializeToJSON(const struct FMainSaveData& data, const TArray<FName>& ActiveQuestsNames, const TArray<FName>& CompletedQuestsNames);

protected:
	TSharedPtr<FJsonObject> SerializeSaveableWorldItem(const struct FSaveableWorldItem& Item);
	TSharedPtr<FJsonObject> SerializeSaveableNpcs(const struct FSaveableWorldNpcs& Npc);
	TSharedPtr<FJsonObject> SerializeWorldDataSave(const struct FWorldDataSave& WorldData);
	TSharedPtr<FJsonObject> SerializePlayerInventory(const TMap<FName, int32>& WorldData);
	TSharedPtr<FJsonObject> SerializeActiveQuests(const TArray<FName>& ActiveQuestsNames);
	TSharedPtr<FJsonObject> SerializeCompletedQuests(const TArray<FName>& CompletedQuestsNames);
	
private:
	FString FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Saved/SaveGames/MyStructData.json"));
	TArray<TSharedPtr<FJsonValue>> SerializeFNameArray(const TArray<FName>& Array);
};
