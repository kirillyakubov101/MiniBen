// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestManager.h"
#include <Signals/Signals.h>
#include <EventBus.h>

// Sets default values for this component's properties
UQuestManager::UQuestManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UQuestManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ..
}

void UQuestManager::FireTestSignal(FString QuestName, int32 AmountToCollect, FString ItemToCollect)
{
	FCollectQuestSignal Signal;
	FString SignalName = Signal.StaticStruct()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Invoking signal: %s"), *SignalName);
	Signal.AmountToCollect = AmountToCollect;
	Signal.ItemToCollect = ItemToCollect;
	Signal.QuestName = QuestName;

	EventBus::GetInst().Invoke(Signal);
}

