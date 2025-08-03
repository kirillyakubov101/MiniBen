// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/MeleeCombatInterface.h"
#include "MeleeCombatHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MINIBEN_API UMeleeCombatHandler : public UActorComponent, public IMeleeCombatInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeCombatHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ProccessDynamicActionSignal();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
