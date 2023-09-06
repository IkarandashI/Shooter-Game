// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SPMenuHUD.h"
#include "UI/SPBaseWidget.h"

void ASPMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<USPBaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
