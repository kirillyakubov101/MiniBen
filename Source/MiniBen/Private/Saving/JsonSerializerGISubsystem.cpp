// Fill out your copyright notice in the Description page of Project Settings.


#include "Saving/JsonSerializerGISubsystem.h"
#include "MyStructs.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

void UJsonSerializerGISubsystem::SerializeToJSON(const FMainSaveData& data, const TArray<FName>& ActiveQuestsNames, const TArray<FName>& CompletedQuestsNames)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	  // Serialize AllLevels (TMap)
	TSharedPtr<FJsonObject> LevelsObject = MakeShared<FJsonObject>();
	for (const auto& Entry : data.AllLevels)
	{
		LevelsObject->SetObjectField(Entry.Key, SerializeWorldDataSave(Entry.Value));
	}

	JsonObject->SetObjectField(TEXT("AllLevels"), LevelsObject);
	JsonObject->SetObjectField("Invetory", SerializePlayerInventory(data.PlayerInventory));

	// Create a single Quests object
	TSharedPtr<FJsonObject> QuestsObject = MakeShared<FJsonObject>();

	// Add both quest arrays as fields to that object
	QuestsObject->SetArrayField(TEXT("ActiveQuests"), SerializeFNameArray(ActiveQuestsNames));
	QuestsObject->SetArrayField(TEXT("CompletedQuests"), SerializeFNameArray(CompletedQuestsNames));

	// Add the Quests object to the main JSON
	JsonObject->SetObjectField(TEXT("Quests"), QuestsObject);

	// Convert to JSON string
	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// Save to file
	FFileHelper::SaveStringToFile(OutputString, *FilePath);
}


TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeSaveableWorldItem(const FSaveableWorldItem& Item)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetBoolField(TEXT("ShouldBeRemoved"), Item.ShouldBeRemoved);
	JsonObject->SetStringField(TEXT("Guid"), Item.Guid.ToString());

	return JsonObject;
}

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeSaveableNpcs(const FSaveableWorldNpcs& Npc)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("NPC_Name"), Npc.NPCName.ToString());
	JsonObject->SetStringField(TEXT("Guid"), Npc.Guid.ToString());
	JsonObject->SetNumberField(TEXT("QuestGiverState"), static_cast<int32>(Npc.QuestGiverState));
	JsonObject->SetBoolField(TEXT("ShouldBeRemoved"), Npc.ShouldBeRemoved);

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


	// Serialize ListOfLevelAssets (TArray)
	TArray<TSharedPtr<FJsonValue>> LevelAssetsArray;
	for (const auto& pair : WorldData.MapOfLevelWorldItems)
	{
		LevelAssetsArray.Add(MakeShared<FJsonValueObject>(SerializeSaveableWorldItem(pair.Value)));
	}

	JsonObject->SetArrayField(TEXT("ListOfLevelAssets"), LevelAssetsArray);
	

	// Serialize List of NPCs 
	TArray<TSharedPtr<FJsonValue>> LevelNpcsArray;
	for (const auto& pair : WorldData.MapOfLevelSaveableNpcs)
	{
		LevelNpcsArray.Add(MakeShared<FJsonValueObject>(SerializeSaveableNpcs(pair.Value)));
	}

	JsonObject->SetArrayField(TEXT("NPCS"), LevelNpcsArray);
	

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

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeActiveQuests(const TArray<FName>& ActiveQuestsNames)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> JsonArray = SerializeFNameArray(ActiveQuestsNames);

	JsonObject->SetArrayField(TEXT("ActiveQuests"), JsonArray);

	return JsonObject;
}

TSharedPtr<FJsonObject> UJsonSerializerGISubsystem::SerializeCompletedQuests(const TArray<FName>& CompletedQuestsNames)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> JsonArray = SerializeFNameArray(CompletedQuestsNames);
	
	JsonObject->SetArrayField(TEXT("CompletedQuests"), JsonArray);

	return JsonObject;
}

TArray<TSharedPtr<FJsonValue>> UJsonSerializerGISubsystem::SerializeFNameArray(const TArray<FName>& Array)
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	for (const FName& Name : Array)
	{
		JsonArray.Add(MakeShared<FJsonValueString>(Name.ToString()));
	}

	return JsonArray;
}


