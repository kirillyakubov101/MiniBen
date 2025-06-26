// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerCanActivate);


class MINIBEN_API GameEventsBroker
{
private:
	GameEventsBroker() {}
	GameEventsBroker(const GameEventsBroker&) = delete;
	GameEventsBroker& operator=(const GameEventsBroker&) = delete;

public:
	static GameEventsBroker& GetInst();

	// Delegates
	FOnPlayerCanActivate OnPlayerCanActivate;
	void BroadcastPlayerCanActivate() { OnPlayerCanActivate.Broadcast(); }
	

};
