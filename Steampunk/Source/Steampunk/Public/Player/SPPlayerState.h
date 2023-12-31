// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPPlayerState.generated.h"


UCLASS()
class STEAMPUNK_API ASPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return  TeamColor; }

    void AddKill() { ++KillsNum; }
    int32 GetKillsNum() { return KillsNum; }
    
    void AddDeath() { ++DeathNum; }
    int32 GetDeathNum() { return DeathNum; }

    void LogInfo();
    
private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathNum = 0;
};
