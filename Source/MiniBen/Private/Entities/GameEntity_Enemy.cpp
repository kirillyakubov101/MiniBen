// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/GameEntity_Enemy.h"

void AGameEntity_Enemy::TakeDamageNative(AActor* Inst, float DamageAmount, FVector HitLocation)
{
	UE_LOG(LogTemp, Error, TEXT("Damage Dealth %f"), DamageAmount);
}

