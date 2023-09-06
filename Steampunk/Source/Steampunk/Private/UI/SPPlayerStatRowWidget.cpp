// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USPPlayerStatRowWidget::SetPlayerName(const FText &Text)
{
    if(!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USPPlayerStatRowWidget::SetKills(const FText &Text)
{
    if(!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USPPlayerStatRowWidget::SetDeaths(const FText &Text)
{
    if(!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void USPPlayerStatRowWidget::SetTeam(const FText &Text)
{
    if(!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

void USPPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if(!PlayerIndicateImage) return;
    PlayerIndicateImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USPPlayerStatRowWidget::SetTeamColor(const FLinearColor &Color)
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
