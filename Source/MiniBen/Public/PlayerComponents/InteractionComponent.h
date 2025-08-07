// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIBEN_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void TryStoreInteract(AActor* Actor);
	void ClearInteraction();
	void TraceProcess();
	void HandleInteract();
protected:


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* InteractAction;
	UPROPERTY(EditAnywhere)
	float TraceDistance;

	UPROPERTY(EditAnywhere)
	float SphereTraceRadius;

	TScriptInterface<IInteractable> CurrentInteractable;
		

private:
	APlayerController* PlayerController;
	TArray<AActor*> ActorsToIgnore;
};
