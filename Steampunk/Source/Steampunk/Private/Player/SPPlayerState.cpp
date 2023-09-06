// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPPlayerState, All, All);

void ASPPlayerState::LogInfo()
{
    UE_LOG(LogSPPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Death: %i"), TeamID, KillsNum, DeathNum)
}
