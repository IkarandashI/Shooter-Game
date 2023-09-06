// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPGameDataWidget.h"
#include "SPGameModeBase.h"
#include "Player/SPPlayerState.h"

int32 USPGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetSPGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USPGameDataWidget::GetTotalRounds() const
{
    const auto GameMode = GetSPGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USPGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetSPGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASPGameModeBase * USPGameDataWidget::GetSPGameMode() const
{
    return GetWorld() ? Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASPPlayerState * USPGameDataWidget::GetSPPlayerState() const
{
    return  GetOwningPlayer() ? Cast<ASPPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
