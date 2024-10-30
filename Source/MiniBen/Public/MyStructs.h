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
		:PlayerHealth(100.f)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float PlayerHealth;
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
		:Guid(FGuid::NewGuid()), ShouldBeRemoved(false)
	{
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
};