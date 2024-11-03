#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestStarter.generated.h"

UCLASS()
class MINIBEN_API AQuestStarter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestStarter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void InitQuestRequiredElements();
};
