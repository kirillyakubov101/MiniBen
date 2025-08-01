// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyStructs.h"
#include "../Interfaces/State.h"
#include "LocomotionStateMachine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIBEN_API ULocomotionStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULocomotionStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SwitchState(EWeaponType WeaponType);
private:
	void InitStartState();
	void TickState(float DeltaTime);
	void SwitchStateProccess();


private:
	TScriptInterface<IState> CurrentState;
		
};
