// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SPMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SPGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/SPLevelItemWidget.h"


DEFINE_LOG_CATEGORY_STATIC(LogSPMenuWidget, All, All)

void USPMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USPMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USPMenuWidget::QuitGame);
    }

    InitLevelItems();
}

void USPMenuWidget::InitLevelItems()
{
    const auto SPGameInstance = GetSPGameInstance();
    if(!SPGameInstance) return;

    checkf(SPGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty"))

    if(!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : SPGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USPLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USPMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }
    if (SPGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(SPGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(SPGameInstance->GetStartupLevel());
    }
}

void USPMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto SPGameInstance = GetSPGameInstance();
    if(!SPGameInstance) return;

    SPGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelecteed(IsSelected);
        }
    }
}

void USPMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
}

void USPMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
    if(Animation != HideAnimation) return;
    
    const auto SPGameInstance = GetSPGameInstance();
    if(!SPGameInstance) return;
    
    UGameplayStatics::OpenLevel(this,SPGameInstance->GetStartupLevel().LevelName);
}

void USPMenuWidget::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USPGameInstance * USPMenuWidget::GetSPGameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USPGameInstance>();
}