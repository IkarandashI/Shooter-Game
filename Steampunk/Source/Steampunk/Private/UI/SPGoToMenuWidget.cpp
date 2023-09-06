// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPGoToMenuWidget.h"
#include "Components/Button.h"
#include "SPGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGoToMenuWidget, All, All)

void USPGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USPGoToMenuWidget::GoToMenu);
    }
}

void USPGoToMenuWidget::GoToMenu()
{
    if(!GetWorld()) return;

    const auto SPGameInstance = GetWorld()->GetGameInstance<USPGameInstance>();
    if(!SPGameInstance) return;

    if (SPGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogGoToMenuWidget, Error, TEXT("Level name is NONE"))
        return;
    }
    UGameplayStatics::OpenLevel(this,SPGameInstance->GetMenuLevelName());
}
