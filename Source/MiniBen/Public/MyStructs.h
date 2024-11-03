#pragma once

#include "CoreMinimal.h"
#include "GameEntity_Enemy.generated.h"
#include "Items/Item.h"
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
struct FQuestRequirment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<AGameEntity_Enemy>, int32> TargetsToKill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<AItem>, int32> TargetsToGather;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ExpReward;
};



USTRUCT(BlueprintType)
struct FQuest : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FQuestRequirment QuestRequirment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDataTableRowHandle> SubQuests;
};

USTRUCT(BlueprintType)
struct FActiveQuestInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	bool bIsDoingMainQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	int32 CurrentSubquestIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	FQuest CurrentQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	FQuest CurrentSubquest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	TMap<TSubclassOf<AItem>, int32> CurrentQuestTargetsToGather;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	TMap<TSubclassOf<AGameEntity_Enemy>, int32> CurrentQuestTargetsToKill;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FActiveQuestInfo ActiveQuestInfo;
};
