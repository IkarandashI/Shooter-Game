// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class STEAMPUNK_API USPGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta=(BindWidget))
    UButton* GoToMenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void GoToMenu();
};
