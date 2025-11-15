#pragma once

#include "CoreMinimal.h"
#include "GameEntity.h"
#include "..\Interfaces\Damageable.h"
#include "Enemies\EnemyAICombatInterface.h"
#include "Enemies\EnemyAIStateInterface.h"
#include "Enemies\BaseEnemeAIController.h"
#include "GameEntity_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AGameEntity_Enemy : public AGameEntity, public IDamageable, public IEnemyAIStateInterface, public IEnemyAICombatInterface
{
	GENERATED_BODY()
	
public:
	// Inherited via IDamageable
	void TakeDamageNative(AActor* Instigator, float DamageAmount, FVector HitLocation) override;

	//// IEnemyAIStateInterface
	AActor* GetCurrentTarget_Implementation() const;
	void SwitchState_Implementation(EEnemyAIStates NewState);
	void SetTarget_Implementation(AActor* NewTarget);
	void ClearTarget_Implementation();
	void CacheStartPositionBeforeChange_Implementation();
	FVector GetStartPositionBeforeChange_Implementation();
	EEnemyAIStates GetStartingState_Implementation();
	EEnemyAIStates GetCurrentState_Implementation();
	bool IsPartOfSavingSystem_Implementation() const;

	// IEnemyAICombatInterface
	void SheathWeapon_Implementation();
	void UnSheathWeapon_Implementation();
	bool IsWeaponReady_Implementation() const;
	void AttackPlayer_Implementation();
	void BeginMeleeTrace_Implementation();
	void EndMeleeTrace_Implementation();
};
