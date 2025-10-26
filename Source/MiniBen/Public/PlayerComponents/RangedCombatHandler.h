// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/RangedCombatInterface.h"
#include "RangedCombatHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API URangedCombatHandler : public UActorComponent, public IRangedCombatInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URangedCombatHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetIsAttackingInRangedForm_Implementation(bool bNewIsAttackingInRangedForm) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttacking = false;

	UFUNCTION(BlueprintNativeEvent)
	void ValidateStateContinue();
		
};
