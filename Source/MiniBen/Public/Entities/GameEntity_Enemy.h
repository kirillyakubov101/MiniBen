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
	virtual AActor* GetCurrentTarget_Implementation() const override;
	virtual void SwitchState_Implementation(EEnemyAIStates NewState) override;
	virtual void SetTarget_Implementation(AActor* NewTarget) override;
	virtual void ClearTarget_Implementation() override;
	virtual void CacheStartPositionBeforeChange_Implementation() override;
	virtual FVector GetStartPositionBeforeChange_Implementation() override;
	virtual EEnemyAIStates GetStartingState_Implementation() override;
	virtual EEnemyAIStates GetCurrentState_Implementation() override;
	virtual bool IsPartOfSavingSystem_Implementation() const override;
	virtual void SetLastKnowPlayerPosition_Implementation(FVector Position) override;
	virtual FVector GetLastKnowPlayerPosition_Implementation() const override;

	// IEnemyAICombatInterface
	virtual void SheathWeapon_Implementation() override;
	virtual void UnSheathWeapon_Implementation() override;
	virtual bool IsWeaponReady_Implementation() const override;
	virtual void AttackPlayer_Implementation() override;
	virtual void BeginMeleeTrace_Implementation() override;
	virtual void EndMeleeTrace_Implementation() override;
	virtual bool IsBlocking_Implementation() const override;
	virtual void TryBlock_Implementation() override;
	virtual void NotifyEnemyAboutIncomingAttack_Implementation() override;
};
