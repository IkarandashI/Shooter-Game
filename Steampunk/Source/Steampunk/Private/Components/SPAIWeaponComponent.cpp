// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SPAIWeaponComponent.h"
#include "Weapon/SPBaseWeapon.h"

void USPAIWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
    Super::StartFire();
}

void USPAIWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextIndex !=CurrentWeaponIndex)
    {
        if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
    Super::NextWeapon();
}
