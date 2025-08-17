// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/QuestProgressWrapper.h"

void UQuestProgressWrapper::BeginDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("UMyObject is being garbage collected!"));

	Super::BeginDestroy();
}

void UQuestProgressWrapper::InitStartValuesOfQuestProgressWrapper(FName currentQuestId, UClass* targetClass, int32 currentAmount, int32 requirement, UClass* wrapperClass)
{
	this->CurrentQuestId = currentQuestId;
	this->TargetClass = targetClass;
	this->CurrentAmount = currentAmount;
	this->Requirement = requirement;
}


void UQuestProgressWrapper::InitializeProgressWrapper()
{
	UE_LOG(LogTemp, Warning, TEXT("InitializeProgressWrapper base called"));
}
