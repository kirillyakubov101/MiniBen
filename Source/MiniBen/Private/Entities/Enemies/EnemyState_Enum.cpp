// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Enemies/EnemyState_Enum.h"
#include "Entities/Enemies/EnemyStructs.h"

UEnemyState_Enum::UEnemyState_Enum()
{
	// Set the enum type pointer here:
	EnumType = StaticEnum<EEnemyAIStates>();

	// Also set the size:
	ValueSize = sizeof(uint8);
}


