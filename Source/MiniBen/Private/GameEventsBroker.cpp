// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventsBroker.h"

GameEventsBroker& GameEventsBroker::GetInst()
{
	static GameEventsBroker Instance;
	return Instance;
}

void GameEventsBroker::UnBindPlayerCanActivate(UObject* Owner)
{
	this->OnPlayerCanActivate.RemoveAll(Owner);
}

void GameEventsBroker::UnBindPlayerDeath(UObject* Owner)
{
	this->OnPlayerDeath.RemoveAll(Owner);
}

void GameEventsBroker::UnBindPlayerLocomotionStateChanged(UObject* Owner)
{
	this->OnPlayerLocomotionStateChanged.RemoveAll(Owner);
}

GameEventsBroker::~GameEventsBroker()
{
	this->OnPlayerCanActivate.Clear();
	this->OnPlayerDeath.Clear();
	this->OnPlayerLocomotionStateChanged.Clear();
}

