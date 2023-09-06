// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SPCoreTypes.h"
#include "SPGameHUD.generated.h"

class USPBaseWidget;

UCLASS()
class STEAMPUNK_API ASPGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESPMatchState, USPBaseWidget*> GameWidgets;

    UPROPERTY()
    USPBaseWidget* CurrentWidget = nullptr;
    
    void DrawCrossHair();
	void OnMatchStateChanged(ESPMatchState State);
};
