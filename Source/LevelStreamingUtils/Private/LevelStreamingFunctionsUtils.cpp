// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamingFunctionsUtils.h"
#include "Engine/LevelStreaming.h"

FString ULevelStreamingFunctionsUtils::ConvertLevelStreamingInstanceToString(ULevelStreaming* StreamingLevel)
{
	// Check if the provided StreamingLevel is valid
	if (StreamingLevel)
	{
		// Get the world asset package name of the streaming level
		FString LevelName = StreamingLevel->GetWorldAssetPackageName();
		return LevelName;
	}

	// If StreamingLevel is null, return an empty string
	return FString("Invalid Level");
}

