// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SPBaseWidget.h"
#include "SPCoreTypes.h"
#include "SPMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USPGameInstance;
class USPLevelItemWidget;

UCLASS()
class STEAMPUNK_API USPMenuWidget : public USPBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta=(BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta=(BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta=(BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta=(BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation;
    
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;

private:
    UPROPERTY()
    TArray<USPLevelItemWidget*> LevelItemWidgets;
    
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void QuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    USPGameInstance* GetSPGameInstance() const;
};
