// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/SPWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"


USPWeaponFXComponent::USPWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USPWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
    auto ImpactData = DefaultImpactData;

    if(Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if(ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }
    // niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

    // decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(),
        ImpactData.DecaleData.Material,
        ImpactData.DecaleData.Size,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());
    if(DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecaleData.LifeTime, ImpactData.DecaleData.FadeOutTime);
    }
}

