// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/State.h"
#include "Interfaces/LocomotionStateMachineInterface.h"
#include "LocomotionStateMachine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIBEN_API ULocomotionStateMachine : public UActorComponent, public ILocomotionStateMachineInterface
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

	void SwitchState_Implementation(EWeaponType WeaponType);

private:
	void InitStartState();
	void TickState(float DeltaTime);
	void SwitchStateProccess(TScriptInterface<IState> NewState);


private:
	TScriptInterface<IState> CurrentState;
		
};
