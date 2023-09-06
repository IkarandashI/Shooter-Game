// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SPAmmopickup.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "SPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASPAmmopickup::GivePickupTo(APawn *PlayerPawn)
{
    const auto HealthComponent = SPUtils::GetSPUPlayerComponent<USPHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = SPUtils::GetSPUPlayerComponent<USPWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;
    
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
