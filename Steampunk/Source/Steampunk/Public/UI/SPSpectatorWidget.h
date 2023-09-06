// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPSpectatorWidget.generated.h"

UCLASS()
class STEAMPUNK_API USPSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetRespawnTime(int32& CountDownTime) const;
};
