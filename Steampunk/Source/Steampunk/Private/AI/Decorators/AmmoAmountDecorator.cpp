// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/AmmoAmountDecorator.h"
#include "AIController.h"
#include "SPUtils.h"
#include "Components/SPWeaponComponent.h"

UAmmoAmountDecorator::UAmmoAmountDecorator()
{
    NodeName = "Need Ammo";
}

bool UAmmoAmountDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;
    
    const auto WeaponComponent = SPUtils::GetSPUPlayerComponent<USPWeaponComponent>(Controller->GetPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
