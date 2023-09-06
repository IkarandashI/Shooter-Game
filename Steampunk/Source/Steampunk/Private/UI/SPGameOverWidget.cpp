// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPGameOverWidget.h"
#include "SPGameModeBase.h"
#include "Player/SPPlayerState.h"
#include "UI/SPPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "SPUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USPGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (GetWorld())
    {
        const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USPGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USPGameOverWidget::OnResetLevel);
    }
}

void USPGameOverWidget::OnMatchStateChanged(ESPMatchState State)
{
    if (State == ESPMatchState::GameOver)
    {
        UpdatePlayerStat();
    }
}

void USPGameOverWidget::UpdatePlayerStat()
{
    if(!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<ASPPlayerState>(Controller->PlayerState);
        if(!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<USPPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if(!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(SPUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(SPUtils::TextFromInt(PlayerState->GetDeathNum()));
        PlayerStatRowWidget->SetTeam(SPUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
        
    }
}

void USPGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
