// Fill out your copyright notice in the Description page of Project Settings.


#include "Saving/SavingSystemSubSystem.h"
#include "MyStructs.h"
#include "Saving/SaveGameContainer.h"
#include "Kismet/GameplayStatics.h"


void USavingSystemSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitSaveSlot();
}

//Assign the save data inside the container right before saving and then SAVE
void USavingSystemSubSystem::SaveGame(const FMainSaveData& MainSaveData)
{
	this->SaveGameContainer->MainSaveData = MainSaveData;
	if (SaveGameContainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameContainer is empty, could not save!!!!"));
		return;
	}
	UGameplayStatics::SaveGameToSlot(SaveGameContainer, SlotName, 0);
}

//Initialize the save slot as new or load existing
void USavingSystemSubSystem::InitSaveSlot()
{
	bool DoesSlotExist = UGameplayStatics::DoesSaveGameExist(SlotName, 0);
	if (DoesSlotExist)
	{
		USaveGame* LoadedGame =  UGameplayStatics::LoadGameFromSlot(SlotName, 0);
		SaveGameContainer = Cast<USaveGameContainer>(LoadedGame);

		if (SaveGameContainer == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("SaveGameContainer is empty, could not Load save slot"));
		}
	}

	else
	{
		USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(USaveGameContainer::StaticClass());
		if (NewSaveGame)
		{
			SaveGameContainer = Cast<USaveGameContainer>(NewSaveGame);
			
			if (SaveGameContainer == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("SaveGameContainer is empty, could not create new save slot"));
			}
		}
	}

	
}

USaveGameContainer* USavingSystemSubSystem::LoadGame()
{
	bool DoesSlotExist = UGameplayStatics::DoesSaveGameExist(SlotName, 0);
	if (!DoesSlotExist) { return nullptr; }

	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	if (!LoadedGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadGame -> !LoadedGame reached"));
		return nullptr;
	}

	SaveGameContainer = Cast<USaveGameContainer>(LoadedGame);

	if (SaveGameContainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameContainer is empty, could not Load save slot"));
		return nullptr;
	}

	return SaveGameContainer;
}

USaveGameContainer* USavingSystemSubSystem::GetSaveData()
{
	if (SaveGameContainer)
	{
		return SaveGameContainer;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetSaveData return NULL SaveGameContainer"));
		return nullptr;
	}
	
}
