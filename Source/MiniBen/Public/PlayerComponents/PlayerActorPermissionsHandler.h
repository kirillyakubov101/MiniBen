// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/PlayerActionPermissions.h"
#include "PlayerActorPermissionsHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDynamicUpdateActionStateSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIBEN_API UPlayerActorPermissionsHandler : public UActorComponent, public IPlayerActionPermissions
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerActorPermissionsHandler();

protected:
	virtual void BeginPlay();

public:	
	virtual void DynamicStateUpdateSignal_Implementation();

	virtual void SetActionState_Implementation(EPlayerActions CharacterAction, bool State);

	virtual bool CanPerformAction_Implementation(EPlayerActions CharacterAction);

public:
	UPROPERTY(BlueprintAssignable)
	FOnDynamicUpdateActionStateSignature DynamicUpdateActionStateDelegate;

	UPROPERTY(EditAnywhere)
	TMap<EPlayerActions, bool> ActionStates;


private:
	void InitializeActionStates();
		
};
