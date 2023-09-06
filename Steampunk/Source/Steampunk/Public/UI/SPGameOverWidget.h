// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SPBaseWidget.h"
#include "SPCoreTypes.h"
#include "SPGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class STEAMPUNK_API USPGameOverWidget : public USPBaseWidget
{
	GENERATED_BODY()


protected:
    UPROPERTY(meta=(BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta=(BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESPMatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
