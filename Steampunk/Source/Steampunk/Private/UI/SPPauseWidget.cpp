// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void USPPauseWidget::NativeOnInitialized()
{
    const auto InitStatus = Super::Initialize();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USPPauseWidget::OnClearPause);   
    }
}

void USPPauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
