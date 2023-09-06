// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STEAMPUNK_API ASPMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
