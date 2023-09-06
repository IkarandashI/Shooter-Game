// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPCoreTypes.h"
#include "SPWeaponFXComponent.generated.h"


class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMPUNK_API USPWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USPWeaponFXComponent();

    void PlayImpactFX(const FHitResult& Hit);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FImpactData DefaultImpactData;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
