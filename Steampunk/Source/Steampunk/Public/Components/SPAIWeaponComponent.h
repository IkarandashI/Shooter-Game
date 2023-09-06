// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SPWeaponComponent.h"
#include "SPAIWeaponComponent.generated.h"


UCLASS()
class STEAMPUNK_API USPAIWeaponComponent : public USPWeaponComponent
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
