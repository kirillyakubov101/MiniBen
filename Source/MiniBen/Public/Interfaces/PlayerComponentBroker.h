// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerComponentBroker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UPlayerComponentBrokerInterface : public UInterface
{
	GENERATED_BODY()
};


class MINIBEN_API IPlayerComponentBrokerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PlayerComponents")
	FVector GetPlayerCameraForward() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IPlayerActionPermissions> GetPlayerActionPermissions();
	virtual class IPlayerActionPermissions* GetPlayerActionPermissionsNative() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IEquipmentInterface> GetEquipmentHandler();
	virtual class IEquipmentInterface* GetEquipmentHandlerNative() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IMeleeCombatInterface> GetMeleeCombatHandler();
	virtual class IMeleeCombatInterface* GetMeleeCombatHandlerNative() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class ILocomotionStateMachineInterface> GetStateMachine();
	virtual class TScriptInterface<class ILocomotionStateMachineInterface> GetStateMachineNative() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IPlayerHealthInterface> GetPlayerHealthHandler();
	virtual class TScriptInterface<class IPlayerHealthInterface> GetPlayerHealthHandlerNative() = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IKillHandlerInterface> GetKillsHandler();
	virtual class TScriptInterface<class IKillHandlerInterface> GetKillsHandlerNative() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IQuestManagerInterface> GetQuestManager();
	virtual class TScriptInterface<class IQuestManagerInterface> GetQuestManagerNative() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerComponents")
	TScriptInterface<class IPlayerInventoryInterface> GetPlayerInventory();
	virtual class TScriptInterface<class IPlayerInventoryInterface> GetPlayerInventoryNative() = 0;
	

};
