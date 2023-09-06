// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPGameDataWidget.generated.h"

class ASPPlayerState;
class ASPGameModeBase;

UCLASS()
class STEAMPUNK_API USPGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetTotalRounds() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundSecondsRemaining() const;

private:
    ASPGameModeBase* GetSPGameMode() const;
    ASPPlayerState* GetSPPlayerState() const;
};
