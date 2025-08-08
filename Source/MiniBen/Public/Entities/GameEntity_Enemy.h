// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEntity.h"
#include "..\Interfaces\Damageable.h"
#include "GameEntity_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AGameEntity_Enemy : public AGameEntity, public IDamageable
{
	GENERATED_BODY()
	

	// Inherited via IDamageable
	void TakeDamageNative(AActor* Instigator, float DamageAmount, FVector HitLocation) override;

};
