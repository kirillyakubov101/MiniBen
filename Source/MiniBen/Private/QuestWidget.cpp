// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "MyStructs.h"
#include "../../PlayerActions/Public/EventBus.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EventBus::GetInst().RegisterHandler<FMySignal>(
		[](const FMySignal& Signal)
		{
			UE_LOG(LogTemp, Warning, TEXT("Handled FMySignal with Amount = %d"), Signal.Amount);
			
		});

}

void UQuestWidget::FireTestSignal()
{
	FMySignal Signal(999);
	EventBus::GetInst().Dispatch(Signal);
}

