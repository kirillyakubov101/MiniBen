// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/State.h"
#include "PlayerStateBase.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API UPlayerStateBase : public UActorComponent, public IState
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateBase();

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void EnterState_Implementation();
	virtual void ExitState_Implementation();
	virtual void TickState_Implementation(float DeltaTime);
};
