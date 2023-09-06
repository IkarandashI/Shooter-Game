// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SPBaseWeapon.h"
#include "SPLauncherWeapon.generated.h"

class ASPProjectile;
/**
 * 
 */
UCLASS()
class STEAMPUNK_API ASPLauncherWeapon : public ASPBaseWeapon
{
	GENERATED_BODY()
public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ASPProjectile> ProjectileClass;
    
    virtual void MakeShot() override;
};
