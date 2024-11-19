// Fill out your copyright notice in the Description page of Project Settings.


#include "Saving/JsonSerializerGISubsystem.h"
#include "MyStructs.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

void UJsonSerializerGISubsystem::SerializeToJSON(const FMainSaveData& data)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	//Character
	JsonObject->SetObjectField("CharacterStats", SerializeCharacterStats(data.PlayerStats)); 

	  // Serialize AllLevels (TMap)
	TSharedPtr<FJsonObject> LevelsObject = MakeShared<FJsonObject>();
	for (const auto& Entry : data.AllLevels)
	{
		LevelsObject->SetObjectField(Entry.Key, SerializeWorldDataSave(Entry.Value));
	}

	JsonObject->SetObjectField(TEXT("AllLevels"), LevelsObject);
	JsonObject->SetObjectField("Invetory", SerializePlayerInventory(data.PlayerInventory));

	// Convert to JSON string
	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// Save to file
	FFileHelper::SaveStringToFile(OutputString, *FilePath);
}

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeCharacterStats(const FCharacterStats& Stats)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	JsonObject->SetNumberField(TEXT("PlayerHealth"), Stats.PlayerHealth);
	JsonObject->SetNumberField(TEXT("PlayerLevel"), Stats.PlayerLevel);
	JsonObject->SetNumberField(TEXT("PlayerExp"), Stats.PlayerExp);


	return JsonObject;
}

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeSaveableWorldItem(const FSaveableWorldItem& Item)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetBoolField(TEXT("ShouldBeRemoved"), Item.ShouldBeRemoved);
	JsonObject->SetStringField(TEXT("Guid"), Item.Guid.ToString());

	return JsonObject;
}

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeWorldDataSave(const FWorldDataSave& WorldData)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetBoolField(TEXT("bHasLevelBeenInitialized"), WorldData.bHasLevelBeenInitialized);

	TSharedPtr<FJsonObject> SublevelsObject = MakeShared<FJsonObject>();

	for (const auto& Entry : WorldData.ListOfSublevels)
	{
		SublevelsObject->SetBoolField(Entry.Key, Entry.Value);
	}

	JsonObject->SetObjectField(TEXT("ListOfSublevels"), SublevelsObject);

	// Serialize PlayerPosition (FVector)
	TSharedPtr<FJsonObject> PositionObject = MakeShared<FJsonObject>();
	PositionObject->SetNumberField(TEXT("X"), WorldData.PlayerPosition.X);
	PositionObject->SetNumberField(TEXT("Y"), WorldData.PlayerPosition.Y);
	PositionObject->SetNumberField(TEXT("Z"), WorldData.PlayerPosition.Z);

	JsonObject->SetObjectField(TEXT("PlayerPosition"), PositionObject);

	// Serialize ListOfLevelAssets (TArray)
	TArray<TSharedPtr<FJsonValue>> LevelAssetsArray;
	for (const FSaveableWorldItem& Item : WorldData.ListOfLevelAssets)
	{
		LevelAssetsArray.Add(MakeShared<FJsonValueObject>(SerializeSaveableWorldItem(Item)));
	}

	JsonObject->SetArrayField(TEXT("ListOfLevelAssets"), LevelAssetsArray);


	return JsonObject;
}

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializePlayerInventory(const TMap<FName, int32>& WorldData)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TSharedPtr<FJsonObject> PlayerInventoryObject = MakeShared<FJsonObject>();

	for (const auto& ele : WorldData)
	{
		PlayerInventoryObject->SetNumberField(ele.Key.ToString(), ele.Value);
	}

	JsonObject->SetObjectField("PlayerInventory", PlayerInventoryObject);

	return JsonObject;
}
