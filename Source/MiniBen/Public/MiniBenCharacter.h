// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../PlayerActions/Public/Saveable.h"
#include "Interfaces/KillHandlerInterface.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/PlayerComponentBroker.h"
#include "MiniBenCharacter.generated.h"


UCLASS()
class MINIBEN_API AMiniBenCharacter : public ACharacter, public ISaveable, public IKillHandlerInterface, public IPlayerInterface, public IPlayerComponentBrokerInterface
{
	GENERATED_BODY()

public:
	AMiniBenCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SavePlayerInventory(const TMap<FName, int32>& inventory);

	UFUNCTION(BlueprintCallable)
	void RestorePlayerInventory(TMap<FName, int32>& Outinventory);

	UFUNCTION(BlueprintImplementableEvent)
	void HandlePlayerDeath();

	// ISaveable Interface
	virtual void SaveAndRecordSelf_Implementation();
	virtual void LoadAndRestoreSelf_Implementation();

	// IKillHandlerInterface Interface
	virtual void SignalEnemyKilled_Implementation(TSubclassOf<class AGameEntity_Enemy> EnemyClass);

	// IPlayerInterface Interface
	virtual bool CanBeTargeted_Implementation();

	// IPlayerComponentBrokerInterface Interface
	virtual UCameraComponent* GetPlayerMainCamera_Implementation() const;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanPlayerBeTargeted;

	UCameraComponent* MainCamera;

private:
	class UMiniBenGameInstance* GameInstance;
	

};
