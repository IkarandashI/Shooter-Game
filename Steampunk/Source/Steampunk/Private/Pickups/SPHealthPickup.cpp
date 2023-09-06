// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SPHealthPickup.h"
#include "Components/SPHealthComponent.h"
#include "SPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASPHealthPickup::GivePickupTo(APawn *PlayerPawn)
{
    const auto HealthComponent = SPUtils::GetSPUPlayerComponent<USPHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;
    return HealthComponent->TryToAddHealth(HealthAmount);
}