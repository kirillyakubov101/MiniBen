#pragma once

#include "CoreMinimal.h"
#include "GameEntity.h"
#include "..\Interfaces\Damageable.h"
#include "Enemies\EnemyAICombatInterface.h"
#include "Enemies\EnemyAIStateInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Enemies\BaseEnemeAIController.h"
#include "GameEntity_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MINIBEN_API AGameEntity_Enemy : public AGameEntity, public IDamageable, public IEnemyAIStateInterface, public IEnemyAICombatInterface, public IGenericTeamAgentInterface
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

	virtual FGenericTeamId GetGenericTeamId() const override
	{
		if (const ABaseEnemeAIController* Ctrl = Cast<ABaseEnemeAIController>(GetController()))
			return Ctrl->GetGenericTeamId();

		return FGenericTeamId::NoTeam;
	}

	// IEnemyAICombatInterface
	void SheathWeapon_Implementation();
	void UnSheathWeapon_Implementation();
	bool IsWeaponReady_Implementation() const;
	void AttackPlayer_Implementation();
	void BeginMeleeTrace_Implementation();
	void EndMeleeTrace_Implementation();
};
