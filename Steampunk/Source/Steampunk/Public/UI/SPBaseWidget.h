// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMPUNK_API USPBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void Show();
    
protected:
    UPROPERTY(meta=(BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
};
