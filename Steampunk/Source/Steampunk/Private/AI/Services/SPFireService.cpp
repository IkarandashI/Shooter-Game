// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/SPFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SPUtils.h"
#include "SPWeaponComponent.h"


USPFireService::USPFireService()
{
    NodeName = "Fire";
}

void USPFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    if (Controller)
    {
        const auto WeaponComponent = SPUtils::GetSPUPlayerComponent<USPWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
