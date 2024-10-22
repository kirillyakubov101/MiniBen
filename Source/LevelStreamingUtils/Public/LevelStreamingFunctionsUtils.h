// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelStreamingFunctionsUtils.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMINGUTILS_API ULevelStreamingFunctionsUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static FString ConvertLevelStreamingInstanceToString(ULevelStreaming* StreamingLevel);
	
};
