// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWorldSubsystem.h"

const TArray<ULevelStreaming*>& UCustomWorldSubsystem::GetAllSubLevels(UWorld* World) const
{
	UWorld* CurrentWorld = nullptr;

	if (World == nullptr)
	{
		CurrentWorld = GetWorld();
	}
	else
	{
		CurrentWorld = World;
	}
	check(CurrentWorld);

	return CurrentWorld->GetStreamingLevels();
}
