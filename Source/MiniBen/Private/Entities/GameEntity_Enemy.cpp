// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/GameEntity_Enemy.h"

void AGameEntity_Enemy::TakeDamageNative(AActor* Inst, float DamageAmount, FVector HitLocation)
{
	UE_LOG(LogTemp, Error, TEXT("Damage Dealth %f"), DamageAmount);
}

AActor* AGameEntity_Enemy::GetCurrentTarget_Implementation() const
{
	return nullptr;
}

void AGameEntity_Enemy::SwitchState_Implementation(EEnemyAIStates NewState)
{
}

void AGameEntity_Enemy::SetTarget_Implementation(AActor* NewTarget)
{
}

void AGameEntity_Enemy::ClearTarget_Implementation()
{
}

void AGameEntity_Enemy::CacheStartPositionBeforeChange_Implementation()
{
}

FVector AGameEntity_Enemy::GetStartPositionBeforeChange_Implementation()
{
	return FVector();
}

EEnemyAIStates AGameEntity_Enemy::GetStartingState_Implementation()
{
	return EEnemyAIStates();
}

EEnemyAIStates AGameEntity_Enemy::GetCurrentState_Implementation()
{
	return EEnemyAIStates();
}

bool AGameEntity_Enemy::IsPartOfSavingSystem_Implementation() const
{
	return false;
}

void AGameEntity_Enemy::SetLastKnowPlayerPosition_Implementation(FVector Position)
{
}

FVector AGameEntity_Enemy::GetLastKnowPlayerPosition_Implementation() const
{
	return FVector();
}


void AGameEntity_Enemy::SheathWeapon_Implementation() 
{

}
void AGameEntity_Enemy::UnSheathWeapon_Implementation()
{

}

bool AGameEntity_Enemy::IsWeaponReady_Implementation() const
{
	return true;
}

void AGameEntity_Enemy::AttackPlayer_Implementation()
{

}

void AGameEntity_Enemy::BeginMeleeTrace_Implementation()
{

}

void AGameEntity_Enemy::EndMeleeTrace_Implementation()
{

}

