// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestProgressWrapper.h"

void UQuestProgressWrapper::BeginDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("UMyObject is being garbage collected!"));

	Super::BeginDestroy();
}
