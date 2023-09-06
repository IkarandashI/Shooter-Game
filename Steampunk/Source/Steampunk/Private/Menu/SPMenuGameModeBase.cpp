// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/SPMenuGameModeBase.h"
#include "Menu/SPMenuPlayerController.h"
#include "Menu/UI/SPMenuHUD.h"

ASPMenuGameModeBase::ASPMenuGameModeBase()
{
    PlayerControllerClass = ASPMenuPlayerController::StaticClass();
    HUDClass = ASPMenuHUD::StaticClass();
}
