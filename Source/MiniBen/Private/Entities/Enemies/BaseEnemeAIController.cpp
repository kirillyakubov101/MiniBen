// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Enemies/BaseEnemeAIController.h"

ABaseEnemeAIController::ABaseEnemeAIController()
{
    TeamID = FGenericTeamId(1);
}

void ABaseEnemeAIController::BeginPlay()
{
	Super::BeginPlay();
}

FGenericTeamId ABaseEnemeAIController::GetGenericTeamId() const
{
    return TeamID;
}

ETeamAttitude::Type ABaseEnemeAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    if (const APawn* OtherPawn = Cast<const APawn>(&Other))
    {
        if (const AController* OtherCtrl = OtherPawn->GetController())
        {
            if (const IGenericTeamAgentInterface* TeamAgent = Cast<const IGenericTeamAgentInterface>(OtherCtrl))
            {
                const auto OtherId = TeamAgent->GetGenericTeamId();
                if (OtherId.GetId() == 255)
                {
                    return ETeamAttitude::Neutral;
                }
                   
                return FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherId);
            }
        }
    }
    return ETeamAttitude::Neutral;
}
