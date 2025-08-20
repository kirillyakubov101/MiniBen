// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerCanActivate);
DECLARE_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_MULTICAST_DELEGATE(FOnPlayerLocomotionStateChanged);


class MINIBEN_API GameEventsBroker
{
public:
	static GameEventsBroker& GetInst();

	// OnPlayerCanActivate
	void BroadcastPlayerCanActivate() { OnPlayerCanActivate.Broadcast(); }

	// OnPlayerDeath
	void BroadcastPlayerDeath() { OnPlayerDeath.Broadcast(); }

	// OnPlayerLocomotionStateChanged
	void BroadcastPlayerLocomotionStateChanged(){}

	void UnBindPlayerCanActivate(UObject* Owner);
	void UnBindPlayerDeath(UObject* Owner);
	void UnBindPlayerLocomotionStateChanged(UObject* Owner);

	template<typename UserClass, typename FuncType>
	void BindToPlayerCanActivate(UserClass* Object, FuncType Func)
	{
		OnPlayerCanActivate.AddUObject(Object, Func);
	}

	template<typename UserClass, typename FuncType>
	void BindToPlayerDeath(UserClass* Object, FuncType Func)
	{
		OnPlayerDeath.AddUObject(Object, Func);
	}

	template<typename UserClass, typename FuncType>
	void BindToPlayerLocomotionStateChanged(UserClass* Object, FuncType Func)
	{
		OnPlayerLocomotionStateChanged.AddUObject(Object, Func);
	}

private:
	GameEventsBroker() {}
	GameEventsBroker(const GameEventsBroker&) = delete;
	GameEventsBroker& operator=(const GameEventsBroker&) = delete;
	virtual ~GameEventsBroker();


private:
	FOnPlayerCanActivate OnPlayerCanActivate;
	FOnPlayerDeath OnPlayerDeath;
	FOnPlayerLocomotionStateChanged OnPlayerLocomotionStateChanged;
};
