// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAIController.h"
#include "AI/SPAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SPAIPerceptionComponent.h"
#include "Components/SPRespawnComponent.h"


ASPAIController::ASPAIController()
{
    SPAIPerceptionComponent = CreateDefaultSubobject<USPAIPerceptionComponent>("SPAIPerceptionComponent");
    SetPerceptionComponent(*SPAIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>("RespawnComponent");

    bWantsPlayerState = true;
}

void ASPAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    
    const auto SPCharacter = Cast<ASPAICharacter>(InPawn);
    if (SPCharacter)
    {
        RunBehaviorTree(SPCharacter->BehaviorTreeAsset);
    }    
}

void ASPAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor * ASPAIController::GetFocusOnActor() const
{
    if(!GetBlackboardComponent()) return  nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
