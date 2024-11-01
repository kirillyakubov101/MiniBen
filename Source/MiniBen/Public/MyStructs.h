#pragma once

#include "CoreMinimal.h"
#include "MyStructs.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
public:
	GENERATED_BODY()

public:

	FCharacterStats()
		:PlayerHealth(100.f), PlayerExp(0), PlayerLevel(1)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats", SaveGame)
	float PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats", SaveGame)
	int32 PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats", SaveGame)
	int32 PlayerExp;
};

USTRUCT(BlueprintType)
struct FSaveableWorldItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool ShouldBeRemoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FGuid Guid;

	FSaveableWorldItem()
		:ShouldBeRemoved(false)
	{
		Guid = FGuid::NewGuid();
	}

	bool operator==(const FSaveableWorldItem& other) const
	{
		return other.Guid == this->Guid;
	}
};

USTRUCT(BlueprintType)
struct FWorldDataSave
{
	GENERATED_BODY()

public:

	FWorldDataSave()
		:bHasLevelBeenInitialized(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool bHasLevelBeenInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FString,bool> ListOfSublevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FVector PlayerPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TArray<FSaveableWorldItem> ListOfLevelAssets;
};

USTRUCT(BlueprintType)
struct FMainSaveData
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FCharacterStats PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FName, int32> PlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FString, FWorldDataSave> AllLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool bHasSaved;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Saveable", SaveGame)
	FName LastSavedLevel;
};

USTRUCT(BlueprintType)
struct FQuestRequirements
{
	GENERATED_BODY()
	//for QT_Kill
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmountToKill;
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	QT_Kill      UMETA(DisplayName = "Kill"),
	QT_Gather    UMETA(DisplayName = "Gather"),
	QT_GoTo      UMETA(DisplayName = "GoTo"),
	QT_TalkTo    UMETA(DisplayName = "TalkTo"),
	QT_Interact  UMETA(DisplayName = "InteractWith")
};

USTRUCT(BlueprintType)
struct FQuest : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExpReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestRequirements QuestRequirements;
};
