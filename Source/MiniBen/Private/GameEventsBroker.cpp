// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventsBroker.h"

GameEventsBroker& GameEventsBroker::GetInst()
{
	static GameEventsBroker Instance;
	return Instance;
}