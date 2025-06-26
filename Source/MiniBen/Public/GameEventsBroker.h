// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerCanActivate);


class MINIBEN_API GameEventsBroker
{
public:
	static GameEventsBroker& GetInst();

	// OnPlayerCanActivate
	void BroadcastPlayerCanActivate() { OnPlayerCanActivate.Broadcast(); }

	template<typename UserClass, typename FuncType>
	void BindToPlayerCanActivate(UserClass* Object, FuncType Func)
	{
		OnPlayerCanActivate.AddUObject(Object, Func);
	}

private:
	GameEventsBroker() {}
	GameEventsBroker(const GameEventsBroker&) = delete;
	GameEventsBroker& operator=(const GameEventsBroker&) = delete;
	virtual ~GameEventsBroker();


private:
	FOnPlayerCanActivate OnPlayerCanActivate;

};
