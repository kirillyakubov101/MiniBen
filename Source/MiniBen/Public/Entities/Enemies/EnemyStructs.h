#pragma once
#include "CoreMinimal.h"
#include "EnemyStructs.generated.h"

UENUM(BlueprintType)
enum class EEnemyAIStates : uint8
{
	ES_None				UMETA(DisplayName = "None"),
	ES_Idle				UMETA(DisplayName = "Idle"),
	ES_Patrol			UMETA(DisplayName = "Patrol"),
	ES_Chase			UMETA(DisplayName = "Chase"),
	ES_Combat			UMETA(DisplayName = "Combat"),
	ES_Stunned			UMETA(DisplayName = "Stunned"),
	ES_Death			UMETA(DisplayName = "Death"),
	ES_EndChase			UMETA(DisplayName = "EndChase"),
	ES_Sheath			UMETA(DisplayName = "Sheath"),
	ES_UnSheath			UMETA(DisplayName = "UnSheath"),
	ES_Investigate 		UMETA(DisplayName = "Investigate"),
	ES_Blocking         UMETA(DisplayName = "Blocking")
};