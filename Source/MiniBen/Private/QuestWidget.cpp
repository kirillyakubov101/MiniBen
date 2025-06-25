// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "MyStructs.h"
#include "../../PlayerActions/Public/EventBus.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	EventBus::GetInst().Subscribe<FCollectQuestSignal>(
		[this](const FCollectQuestSignal& Signal)
		{
			this->UpdateQuestHUD(Signal);
		});
	
}

void UQuestWidget::UpdateQuestHUD(const FCollectQuestSignal& Signal)
{
	UE_LOG(LogTemp, Warning, TEXT("Quest: %s Amount: %d Item to collect: %s"), *Signal.QuestName, Signal.AmountToCollect, *Signal.ItemToCollect);
}

