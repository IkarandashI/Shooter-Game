// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/SPBaseWidget.h"
#include "SPGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPGameHUD, All, All);

void ASPGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void ASPGameHUD::BeginPlay()
{
    Super::BeginPlay();


    GameWidgets.Add(ESPMatchState::InProgress,CreateWidget<USPBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESPMatchState::Pause,CreateWidget<USPBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESPMatchState::GameOver,CreateWidget<USPBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair: GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if(!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASPGameHUD::OnMatchStateChanged);
        }
    }
}

void ASPGameHUD::OnMatchStateChanged(ESPMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }
    
    UE_LOG(LogSPGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}

void ASPGameHUD::DrawCrossHair()
{
    const TInterval<float> Centre(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;
    
    DrawLine(Centre.Min - HalfLineSize, Centre.Max, Centre.Min + HalfLineSize, Centre.Max, LineColor, LineThickness);
    DrawLine(Centre.Min, Centre.Max - HalfLineSize, Centre.Min, Centre.Max + HalfLineSize, LineColor, LineThickness);
}
