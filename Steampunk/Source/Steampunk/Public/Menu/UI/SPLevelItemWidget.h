// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPCoreTypes.h"
#include "SPLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class STEAMPUNK_API USPLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const { return LevelData; }

    void SetSelecteed(bool IsSelected);
protected:
    UPROPERTY(meta=(BindWidget))
    UButton* LevelSelectedButton;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta=(BindWidget))
    UImage* LevelImage;

    UPROPERTY(meta=(BindWidget))
    UImage* FrameImage;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelItemClicked();

    UFUNCTION()
    void OnLevelItemHovered();
    
    UFUNCTION()
    void OnLevelItemUnhovered();
};
