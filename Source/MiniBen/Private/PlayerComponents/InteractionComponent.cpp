// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

UInteractionComponent::UInteractionComponent():CurrentInteractable{nullptr}, PlayerController{nullptr}
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ActorsToIgnore.Add(PlayerController->GetPawn());

	UInputComponent* InputComponent = GetOwner()->InputComponent;
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner has no InputComponent"));
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner's InputComponent is not an EnhancedInputComponent"));
		return;
	}

	EnhancedInputComponent->BindAction(this->InteractAction, ETriggerEvent::Started, this, &UInteractionComponent::HandleInteract);
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceProcess();
}

void UInteractionComponent::TryStoreInteract(AActor* Actor)
{
	if (Actor == nullptr) { return; }

	if (Actor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		if (CurrentInteractable.GetObject() != Actor)
		{
			CurrentInteractable = Actor;
		}
	}

}

void UInteractionComponent::ClearInteraction()
{
	this->CurrentInteractable = nullptr;
}

void UInteractionComponent::TraceProcess()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	
	

	FVector End = CameraLocation + (CameraRotation.Vector() * this->TraceDistance);

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		CameraLocation,
		End,
		this->SphereTraceRadius,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	if (bHit)
	{
		TryStoreInteract(HitResult.GetActor());
	}
	else
	{
		ClearInteraction();
	}
}

void UInteractionComponent::HandleInteract()
{
	if (CurrentInteractable.GetObject())
	{
		IInteractable::Execute_Interact(CurrentInteractable.GetObject());
	}
}

