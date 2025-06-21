// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseStats.h"

FPrimaryAssetId UEnemyBaseStats::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(this->DataAssetType, GetFName());
}
