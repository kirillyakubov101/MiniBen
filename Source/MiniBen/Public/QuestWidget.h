// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"




UCLASS()
class MINIBEN_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;
	void UpdateQuestHUD();
};
