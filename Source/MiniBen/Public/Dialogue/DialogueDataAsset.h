// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FDialogueChoice
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText ChoiceText;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 TargetNodeID = -1;

    // FLAGS TO SET AFTER SELECTION
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> ResultFlags;

    // EVENT TAGS / COMMANDS
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> EventTags;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Text;

    // CONDITIONS NEEDED TO SHOW THIS NODE
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> RequiredFlags;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FDialogueChoice> Choices;
};


UCLASS()
class MINIBEN_API UDialogueDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FDialogueNode> Nodes;

    // Optional: Starting Node ID for this NPC
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 RootNodeID = 0;

    // Override the GetPrimaryAssetId function to return the asset ID based on ItemType and ItemID
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(AssetType, DialogueAssetId);
    }


    const FName GetItemName() const
    {
        return DialogueAssetId;
    }

    virtual void PostLoad() override
    {
		Super::PostLoad();
        if (DialogueAssetId.IsNone())
        {
            DialogueAssetId = GetFName();  // Uses the object/asset name
        }
    }


protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
    FPrimaryAssetType AssetType = "Dialogue";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
    FName DialogueAssetId;
	
};
