
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "EnemyState_Enum.generated.h"

UCLASS(EditInlineNew, meta = (DisplayName = "Enemy AI State"))
class MINIBEN_API UEnemyState_Enum : public UBlackboardKeyType_Enum
{
	GENERATED_BODY()

public:
	UEnemyState_Enum();
	
};
