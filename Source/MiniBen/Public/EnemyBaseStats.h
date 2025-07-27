// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyBaseStats.generated.h"


USTRUCT(BlueprintType)
struct FEnemyBaseStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ChaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;
};


USTRUCT(BlueprintType)
struct FEnemyRuntimeStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	// TODO: this needs to be created either on BP or called from Native
	void InitFromBaseStats(const FEnemyBaseStat& Base)
	{
		this->MoveSpeed = Base.MoveSpeed;
		this->MinAttackDamage = Base.MinAttackDamage;
		this->MaxAttackDamage = Base.MaxAttackDamage;
		this->ChaseSpeed = Base.ChaseSpeed;
		this->MaxHealth = Base.MaxHealth;
	}
};

UCLASS(BlueprintType)
class MINIBEN_API UEnemyBaseStats : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	FEnemyBaseStat EnemyBaseStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Params")
	FPrimaryAssetType DataAssetType = "EnemyStats";

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
	