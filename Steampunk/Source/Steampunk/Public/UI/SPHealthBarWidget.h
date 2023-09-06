// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class STEAMPUNK_API USPHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetHealthPercent(float Percent);

protected:
    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthProgressBar;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    float PercentVisibilityThreshold = 0.9f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor BadColor = FLinearColor::Red;
};
