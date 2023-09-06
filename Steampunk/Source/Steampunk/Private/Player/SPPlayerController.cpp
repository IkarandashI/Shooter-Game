// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"
#include "Components/SPRespawnComponent.h"
#include "SPGameModeBase.h"

ASPPlayerController::ASPPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USPRespawnComponent>("RespawnComponent");
}

void ASPPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (GetWorld())
    {
        const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASPPlayerController::OnMatchStateChanged);
        }
    }
}

void ASPPlayerController::OnMatchStateChanged(ESPMatchState State)
{
    if (State == ESPMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASPPlayerController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void ASPPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASPPlayerController::OnPauseGame);
}

void ASPPlayerController::OnPauseGame()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

