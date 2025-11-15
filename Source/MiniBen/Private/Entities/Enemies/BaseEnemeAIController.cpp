// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Enemies/BaseEnemeAIController.h"

ABaseEnemeAIController::ABaseEnemeAIController()
{
    TeamID = FGenericTeamId(1);
}

void ABaseEnemeAIController::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Controller TeamID: %d"), GetGenericTeamId().GetId());
}

FGenericTeamId ABaseEnemeAIController::GetGenericTeamId() const
{
    return TeamID;
}

ETeamAttitude::Type ABaseEnemeAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    UE_LOG(LogTemp, Warning, TEXT("Trying: %s"), *Other.GetName());
    if (const APawn* OtherPawn = Cast<const APawn>(&Other))
    {
        if (const AController* OtherCtrl = OtherPawn->GetController())
        {
            if (const IGenericTeamAgentInterface* TeamAgent = Cast<const IGenericTeamAgentInterface>(OtherCtrl))
            {
                const auto OtherId = TeamAgent->GetGenericTeamId();
                UE_LOG(LogTemp, Warning, TEXT("OtherTeamID: %d | MyTeamID: %d"), OtherId.GetId(), TeamID.GetId());
                return FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherId);
            }
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("No IGenericTeamAgentInterface found on: %s"), *Other.GetName());
    return ETeamAttitude::Neutral;
}
