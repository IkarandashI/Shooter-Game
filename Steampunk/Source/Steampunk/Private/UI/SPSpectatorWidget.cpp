// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPSpectatorWidget.h"
#include "SPUtils.h"
#include "Components/SPRespawnComponent.h"

bool USPSpectatorWidget::GetRespawnTime(int32 &CountDownTime) const
{
    const auto RespawnComponent = SPUtils::GetSPUPlayerComponent<USPRespawnComponent>(GetOwningPlayer());
    if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime= RespawnComponent->GetRespawnCountDown();
    return true;
}
