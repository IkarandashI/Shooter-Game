// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SPLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USPLevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LevelSelectedButton)
    {
        LevelSelectedButton->OnClicked.AddDynamic(this, &USPLevelItemWidget::OnLevelItemClicked);
        LevelSelectedButton->OnHovered.AddDynamic(this, &USPLevelItemWidget::OnLevelItemHovered);
        LevelSelectedButton->OnUnhovered.AddDynamic(this, &USPLevelItemWidget::OnLevelItemUnhovered);
    }
}

void USPLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USPLevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void USPLevelItemWidget::SetSelecteed(bool IsSelected)
{
   if(LevelImage)
   {
       LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
   }
}

void USPLevelItemWidget::OnLevelItemHovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USPLevelItemWidget::OnLevelItemUnhovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}