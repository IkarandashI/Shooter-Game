// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/SPHealthPercentDecorator.h"
#include "AIController.h"
#include "SPUtils.h"
#include "Components/SPHealthComponent.h"

USPHealthPercentDecorator::USPHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USPHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto HealthComponent = SPUtils::GetSPUPlayerComponent<USPHealthComponent>(Controller->GetPawn());
    if(!HealthComponent || HealthComponent->IsDead()) return false;
    
    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
