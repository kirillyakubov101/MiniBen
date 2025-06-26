// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "GameEventsBroker.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameEventsBroker::GetInst().BindToPlayerCanActivate(this, &UQuestWidget::UpdateQuestHUD);
}

void UQuestWidget::UpdateQuestHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("UE UpdateQuestHUD UPDATED!"));
}


