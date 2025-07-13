#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Quests/QuestStarter.h"
#include "Entities/GameEntity_Enemy.h"
#include "MyStructs.generated.h"

//ENUMS
UENUM(BlueprintType)
enum class EQuestType : uint8
{
	QT_Kill      UMETA(DisplayName = "Kill"),
	QT_Gather    UMETA(DisplayName = "Gather"),
	QT_GoTo      UMETA(DisplayName = "GoTo"),
	QT_TalkTo    UMETA(DisplayName = "TalkTo"),
	QT_Interact  UMETA(DisplayName = "InteractWith")
};

UENUM(BlueprintType)
enum class EQuestGiverState : uint8
{
	QGS_None                 UMETA(DisplayName = "None"),
	QGS_GotQuest		     UMETA(DisplayName = "GotQuest"),
	QGS_QuestInProgress      UMETA(DisplayName = "QuestInProgress"),
};


//STRUCTS

USTRUCT(BlueprintType)
struct FPlayerTransformData
{
public:
	GENERATED_BODY()

public:

	FPlayerTransformData()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats", SaveGame)
	FTransform PlayerTransform;
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
		:ShouldBeRemoved(false), Guid(FGuid())
	{
	}

	bool operator==(const FSaveableWorldItem& other) const
	{
		return other.Guid == this->Guid;
	}
};

USTRUCT(BlueprintType)
struct FSaveableWorldNpcs
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FName NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool ShouldBeRemoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FGuid Guid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	EQuestGiverState QuestGiverState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	int32 CurrentQuestIndex = 0;

	FSaveableWorldNpcs()
		:ShouldBeRemoved(false), Guid(FGuid()), QuestGiverState(EQuestGiverState::QGS_None)
	{
	}

	bool operator==(const FSaveableWorldNpcs& other) const
	{
		return other.Guid == this->Guid;
	}
};

USTRUCT(BlueprintType)
struct FSavealbeWorldEnemy
{
	GENERATED_BODY()

public:
	FSavealbeWorldEnemy() :ShouldBeRemoved(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool ShouldBeRemoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FGuid Guid;

	bool operator==(const FSavealbeWorldEnemy& other) const
	{
		return other.Guid == this->Guid;
	}
};

USTRUCT(BlueprintType)
struct FWorldDataSave
{
	GENERATED_BODY()

public:

	FWorldDataSave() :bHasLevelBeenInitialized(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool bHasLevelBeenInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FString,bool> ListOfSublevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FGuid,FSaveableWorldNpcs> MapOfLevelSaveableNpcs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FGuid, FSaveableWorldItem> MapOfLevelWorldItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FGuid, FSavealbeWorldEnemy> MapOfLevelSaveableEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	FPlayerTransformData PlayerTransformData;
};


USTRUCT(BlueprintType)
struct FQuestRequirment
{
	GENERATED_BODY()

public:

	FQuestRequirment()
		:ExpReward(0), QuestType(EQuestType::QT_GoTo)
	{
	}

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

	FQuest()
		:QuestTitle(FText()), QuestDescription(FText()), QuestRequirment(FQuestRequirment())
	{
	}
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FQuestRequirment QuestRequirment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDataTableRowHandle> SubQuests;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AQuestStarter> QuestStarterClass;
};

USTRUCT(BlueprintType) //TODO: remove later
struct FActiveQuestInfo
{
	GENERATED_BODY()

public:
	FActiveQuestInfo():bIsDoingMainQuest(false), CurrentSubquestIndex(0)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	bool bIsDoingMainQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	int32 CurrentSubquestIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	FQuest CurrentQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable | Quest", SaveGame)
	FQuest CurrentSubquest;
};

USTRUCT(BlueprintType)
struct FMainSaveData
{
	GENERATED_BODY()
public:

	FMainSaveData():bHasSaved(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FName, int32> PlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	TMap<FString, FWorldDataSave> AllLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saveable", SaveGame)
	bool bHasSaved;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Saveable", SaveGame)
	FName LastSavedLevel;
};

