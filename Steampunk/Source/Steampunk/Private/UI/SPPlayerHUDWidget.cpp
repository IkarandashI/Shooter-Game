// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPPlayerHUDWidget.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "SPUtils.h"
#include "Components/ProgressBar.h"
#include "Player/SPPlayerState.h"

void USPPlayerHUDWidget::NativeOnInitialized()
{
    Super::Initialize();
    
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USPPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }    
    
}

void USPPlayerHUDWidget::OnNewPawn(APawn *NewPawn)
{
    const auto HealthComponent = SPUtils::GetSPUPlayerComponent<USPHealthComponent>(NewPawn);
    if(HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USPPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}



void USPPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();

        if(!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }
    UpdateHealthBar();
}

float USPPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = SPUtils::GetSPUPlayerComponent<USPHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USPPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = SPUtils::GetSPUPlayerComponent<USPWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USPPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = SPUtils::GetSPUPlayerComponent<USPWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USPPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = SPUtils::GetSPUPlayerComponent<USPHealthComponent>(GetOwningPlayerPawn());
    return  HealthComponent && !HealthComponent->IsDead();
}

bool USPPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return  Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 USPPlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if(!Controller) return 0;

    const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

void USPPlayerHUDWidget::UpdateHealthBar()
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}

FString USPPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }
    return BulletStr;
}