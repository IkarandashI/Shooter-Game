// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/SPMenuPlayerController.h"

void ASPMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor=true;
}
