 // Fill out your copyright notice in the Description page of Project Settings.


#include "SPWeaponComponent.h"
#include "Weapon/SPBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SPEquipFinishedAnimNotify.h"
#include "Animations/SPReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

constexpr static int32 WeaponNum = 2;

USPWeaponComponent::USPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

 void USPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon"), WeaponNum);

    CurrentWeaponIndex = 0.f;
    InitAnimations();
	SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

 void USPWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
 {
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
 }

 void USPWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character || !GetWorld()) return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASPBaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon) continue;

        Weapon->OnClipEmpty.AddUObject(this, &USPWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USPWeaponComponent::AttachWeaponToSocket(ASPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if(!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

 void USPWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT(" Invalid Weapon"));
        return;
    }
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    if(CurrentWeapon)
    {
        CurrentWeapon->Zoom(false);
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    //CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
        {return Data.WeaponClass == CurrentWeapon->GetClass();});
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
 }


 void USPWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void USPWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

 void USPWeaponComponent::NextWeapon()
 {
     if (!CanEquip()) return;
     
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
 }

 void USPWeaponComponent::PlayAnimMontage(UAnimMontage *Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    Character->PlayAnimMontage(Animation);
}

 void USPWeaponComponent::InitAnimations()
 {
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USPEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USPWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
        checkNoEntry();
    }

    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USPReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
            checkNoEntry();
        }
        ReloadFinishedNotify->OnNotified.AddUObject(this, &USPWeaponComponent::OnReloadFinished);
         
    }
 }

 void USPWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
 {
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character|| Character->GetMesh() != MeshComponent) return;
    
    EquipAnimInProgress = false;
 }

void USPWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character|| Character->GetMesh() != MeshComponent) return;
    
    ReloadAnimInProgress = false;
}

 bool USPWeaponComponent::CanFire() const
 {
    return  CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
 }

 bool USPWeaponComponent::CanEquip() const
 {
    return  !EquipAnimInProgress && !ReloadAnimInProgress;
 }

bool USPWeaponComponent::CanReload() const
{
    return  CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

 void USPWeaponComponent::Reload()
{
    ChangeClip();
}

 void USPWeaponComponent::OnEmptyClip(ASPBaseWeapon* AmmoEmptyWeapon)
 {
    if(!AmmoEmptyWeapon) return;
    
    if(CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (const auto Weapon : Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
    
 }

 void USPWeaponComponent::ChangeClip()
 {
    if(!CanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
 }

bool USPWeaponComponent::GetWeaponUIData(FWeaponUIData &UIData) const
{
    {
        if(CurrentWeapon)
        {
            UIData = CurrentWeapon->GetUIData();
            return true;
        }
        return false;
    }
}

bool USPWeaponComponent::GetWeaponAmmoData(FAmmoData &AmmoData) const
{
    {
        if(CurrentWeapon)
        {
            AmmoData = CurrentWeapon->GetAmmoData();
            return true;
        }
        return false;
    }
}

 bool USPWeaponComponent::TryToAddAmmo(TSubclassOf<ASPBaseWeapon> WeaponType, int32 ClipsAmount)
 {
    for(const auto Weapon: Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
 }

bool USPWeaponComponent::NeedAmmo(TSubclassOf<ASPBaseWeapon> WeaponType)
{
    for(const auto Weapon: Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return !Weapon->IsAmmoFull();
        }
    }
    return false;
}

 void USPWeaponComponent::Zoom(bool Enabled)
 {
     if (CurrentWeapon)
     {
         CurrentWeapon->Zoom(Enabled);
     }
 }
