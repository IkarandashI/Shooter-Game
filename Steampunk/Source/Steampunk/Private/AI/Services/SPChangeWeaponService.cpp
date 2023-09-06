// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/SPChangeWeaponService.h"
#include "Components/SPWeaponComponent.h"
#include "AIController.h"
#include "SPUtils.h"

USPChangeWeaponService::USPChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USPChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = SPUtils::GetSPUPlayerComponent<USPWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
