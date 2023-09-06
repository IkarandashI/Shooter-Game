// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SPBaseWidget.h"
#include "SPPauseWidget.generated.h"

class UButton;

UCLASS()
class STEAMPUNK_API USPPauseWidget : public USPBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;
    
private:
    UFUNCTION()
    void OnClearPause();
};
