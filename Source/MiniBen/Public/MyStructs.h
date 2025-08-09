#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Quests/QuestStarter.h"
#include "MyStructs.generated.h"

class AGameEntity_Enemy;


//ENUMS

UENUM(BlueprintType)
enum class EPlayerActions : uint8
{
	PA_None				UMETA(DisplayName = "None"),
	PA_MidRolling		UMETA(DisplayName = "MidRolling"),
	PA_Attacking		UMETA(DisplayName = "Attacking"),
	PA_Sheath			UMETA(DisplayName = "Sheath"),
	PA_UnSheath			UMETA(DisplayName = "UnSheath"),
	PA_Stagger			UMETA(DisplayName = "Stagger"),
	PA_Dead				UMETA(DisplayName = "Dead"),
	PA_Air				UMETA(DisplayName = "Air"),
	PA_MidSheath		UMETA(DisplayName = "MidSheath"),
};


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_Fists				UMETA(DisplayName = "Fists"),
	WT_OneHandedWeapon		UMETA(DisplayName = "OneHandedWeapon"),
	WT_TwoHandedWeapon      UMETA(DisplayName = "TwoHandedWeapon"),
	WT_Bow					UMETA(DisplayName = "Bow"),
	WT_Unarmed				UMETA(DisplayName = "Unarmed"),
};

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	MS_Normal					 UMETA(DisplayName = "Normal"),
	MS_FistCombat			     UMETA(DisplayName = "FistCombat"),
	MS_OneHandedSwordCombat      UMETA(DisplayName = "OneHandedSwordCombat"),
	MS_Locked					 UMETA(DisplayName = "Locked"),
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

UENUM(BlueprintType)
enum class EQuestGiverState : uint8
{
	QGS_None                 UMETA(DisplayName = "None"),
	QGS_GotQuest		     UMETA(DisplayName = "GotQuest"),
	QGS_QuestInProgress      UMETA(DisplayName = "QuestInProgress"),
};


//STRUCTS

USTRUCT(BlueprintType)
struct FEnemyKillQuest
{
public:
	GENERATED_BODY()

	FEnemyKillQuest():AmountToKill(0)
	{
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TSubclassOf<AGameEntity_Enemy> EnemyToKillClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 AmountToKill;
};

USTRUCT(BlueprintType)
struct FItemGatherQuest
{
public:
	GENERATED_BODY()

	FItemGatherQuest() :AmountToGather(0)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TSubclassOf<AItem> ItemToGatherClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 AmountToGather;
};

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
	FGuid Guid;

	FSaveableWorldItem()
		:/*ShouldBeRemoved(false), */Guid(FGuid())
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEnemyKillQuest TargetsToKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemGatherQuest TargetsToGather;

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

USTRUCT(BlueprintType)
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

