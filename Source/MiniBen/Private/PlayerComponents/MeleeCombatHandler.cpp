// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponents/MeleeCombatHandler.h"
#include "Interfaces/PlayerComponentBroker.h"
#include "Interfaces/PlayerActionPermissions.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/CharacterMeshInterface.h"

// Sets default values for this component's properties
UMeleeCombatHandler::UMeleeCombatHandler()
	:TraceChannel(ECollisionChannel::ECC_Visibility)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeleeCombatHandler::BeginPlay()
{
	Super::BeginPlay();

	IPlayerComponentBrokerInterface* Broker = Cast<IPlayerComponentBrokerInterface>(GetOwner());
	if (Broker)
	{
		
		IPlayerActionPermissions* Permissions = Broker->GetPlayerActionPermissionsNative();
		if (Permissions)
		{
			Permissions->GetOnDynamicUpdateActionState().AddUObject(this, &UMeleeCombatHandler::ValidateStateContinue);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Permissions is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Broker is null"));
	}
	
}


// Called every frame
void UMeleeCombatHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAttackMidway)
	{
		RotateCharacterToFaceForward_Implementation(DeltaTime);
		
	}
	
}

void UMeleeCombatHandler::AssignNewWeapon_Implementation(UWeaponDataAsset* WeaponData)
{
	this->CurrentWeapon = WeaponData;
	this->ListOfAttacks.Empty();
	this->AmountOfAttacks = this->CurrentWeapon->ListOfAttacks.Num();
	LoadAttackAnimations(this->CurrentWeapon->ListOfAttacks);
}

void UMeleeCombatHandler::AttackCommand_Implementation()
{
	if (bIsAttackMidway)
	{
		bIsAttackQueued = true;
	}
	else
	{
		bIsAttackMidway = true;
		SetComponentTickEnabled(true);
		PlayAttackSequanceEvent();
	}
}

void UMeleeCombatHandler::RotateCharacterToFaceForward_Implementation(float DeltaTime)
{
	// Get camera forward vector and convert to yaw-only rotation (ignore pitch and roll)
	FVector CameraForward = IPlayerComponentBrokerInterface::Execute_GetPlayerCameraForward(GetOwner());
	FRotator TargetRotation = CameraForward.ToOrientationRotator();
	TargetRotation.Pitch = 0.0f;
	TargetRotation.Roll = 0.0f;

	// Get current actor rotation
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	// Interpolate towards the target rotation
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationTowardsCameraForwardSpeed);

	// Set the new rotation
	GetOwner()->SetActorRotation(NewRotation);
}

void UMeleeCombatHandler::EndSingleTargetTrace_Implementation()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(AttackTraceTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTraceTimer);
	}
}

void UMeleeCombatHandler::BeginSingleTargetTrace_Implementation()
{
		GetWorld()->GetTimerManager().SetTimer(
			AttackTraceTimer,
			this,
			&UMeleeCombatHandler::TraceSingel,
			0.01f,
			true
		);
}

void UMeleeCombatHandler::ComboEnd_Implementation()
{
	bIsAttackQueued = false;
	bIsAttackMidway = false;
	CurrentAttackIndex = 0;
	TScriptInterface<IPlayerActionPermissions> PlayerActionPermission = IPlayerComponentBrokerInterface::Execute_GetPlayerActionPermissions(GetOwner());
	IPlayerActionPermissions::Execute_SetActionState(PlayerActionPermission.GetObject(), EPlayerActions::PA_Attacking, false);
	SetComponentTickEnabled(false);
}

void UMeleeCombatHandler::ComboNext_Implementation()
{
	CurrentAttackIndex++;
	if (CurrentAttackIndex > AmountOfAttacks)
	{
		ComboEnd_Implementation();
	}
	else
	{
		if (bIsAttackQueued)
		{
			bIsAttackQueued = false;
			PlayAttackSequanceEvent();
		}
	}

}

void UMeleeCombatHandler::PlayAttackSequanceEvent()
{
	USkeletalMeshComponent* OwnerSkeletalMesh = ICharacterMeshInterface::Execute_GetCharacterSkeletalMesh(GetOwner());
	UAnimInstance* AnimInstance = OwnerSkeletalMesh->GetAnimInstance();
	if (ListOfAttacks.IsValidIndex(CurrentAttackIndex))
	{
		UAnimMontage* MontageToPlay = ListOfAttacks[CurrentAttackIndex];

		if (MontageToPlay)
		{
			AnimInstance->Montage_Play(MontageToPlay);
		}
	}
	
}

void UMeleeCombatHandler::TraceSingel()
{
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	FTransform RightHandTranform = ICombatInterface::Execute_GetRightHandTransform(GetOwner());
	FVector Start = RightHandTranform.GetLocation();
	FRotator RightHandRotation = RightHandTranform.GetRotation().Rotator();
	FVector End = Start + (RightHandRotation.RotateVector(FVector::UpVector) * this->CurrentWeapon->AttackRange);
	FHitResult HitResult;

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		this->TraceChannel,
		FCollisionShape::MakeSphere(AttackCollisionSphere),
		QueryParams
	);
	//DrawDebugCapsule(GetWorld(), Start, this->CurrentWeapon->AttackRange, 5.f, RightHandRotation.Quaternion(), !bHit ? FColor::Red : FColor::Green, true, 1.f);
	
	if (bHit)
	{
		bool isDamageable = HitResult.GetActor()->GetClass()->ImplementsInterface(UDamageable::StaticClass());
		if (isDamageable)
		{
			IDamageable::Execute_TakeDamage(HitResult.GetActor(), GetOwner(), CurrentWeapon->DamageAmount, HitResult.ImpactPoint);
			EndSingleTargetTrace_Implementation();
		}
	}
}

void UMeleeCombatHandler::LoadAttackAnimations(const TArray<TSoftObjectPtr<UAnimMontage>>& SoftListOfAnimations)
{
	TArray<FSoftObjectPath> AssetsToLoad;

	for (const TSoftObjectPtr<UAnimMontage> SoftPtr : SoftListOfAnimations)
	{
		if (SoftPtr.IsNull()) { continue; }

		//If the anim was loaded
		if (SoftPtr.IsValid())
		{
			this->ListOfAttacks.Add(SoftPtr.Get()); // anim already loaded, no need to reload
		}
		else
		{
			AssetsToLoad.Add(SoftPtr.ToSoftObjectPath());
		}
	}

	if (AssetsToLoad.Num() == 0)
	{
		// All already loaded
		UE_LOG(LogTemp, Warning, TEXT("All animations already loaded. AssetsToLoad is empty"));
		return;
	}

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	Streamable.RequestAsyncLoad(
		AssetsToLoad,
		FStreamableDelegate::CreateUObject(this, &UMeleeCombatHandler::OnAttackAnimationsLoaded, SoftListOfAnimations),
		FStreamableManager::AsyncLoadHighPriority
	);
}

void UMeleeCombatHandler::OnAttackAnimationsLoaded(TArray<TSoftObjectPtr<UAnimMontage>> SoftListOfAnimations)
{
	// the animations are now loaded
	for (const TSoftObjectPtr<UAnimMontage>& SoftPtr : SoftListOfAnimations)
	{
		UAnimMontage* AnimMontage = SoftPtr.Get();

		if (AnimMontage != nullptr)
		{
			this->ListOfAttacks.Add(AnimMontage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load anim montage: %s"), *SoftPtr.ToString());
		}
	}
}

void UMeleeCombatHandler::ValidateStateContinue()
{
	IPlayerComponentBrokerInterface* Broker = Cast<IPlayerComponentBrokerInterface>(GetOwner());

	TScriptInterface<IPlayerActionPermissions> Permissions = IPlayerComponentBrokerInterface::Execute_GetPlayerActionPermissions(GetOwner());
	bool CanStillAttack = IPlayerActionPermissions::Execute_CanPerformAction(Permissions.GetObject(), EPlayerActions::PA_Attacking);
	if (!CanStillAttack)
	{
		this->ComboEnd_Implementation();
	}
}

