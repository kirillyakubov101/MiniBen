#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyStructs.h"
#include "EnemyAIStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyAIStateInterface : public UInterface
{
	GENERATED_BODY()
};

class MINIBEN_API IEnemyAIStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	AActor* GetCurrentTarget() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	void SwitchState(EEnemyAIStates NewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	void ClearTarget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	void CacheStartPositionBeforeChange();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	FVector GetStartPositionBeforeChange();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	EEnemyAIStates GetStartingState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	EEnemyAIStates GetCurrentState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	bool IsPartOfSavingSystem() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	void SetLastKnowPlayerPosition(FVector Position);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemyAIState")
	FVector GetLastKnowPlayerPosition() const;
	
	
};
