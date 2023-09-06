// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "SPPlayerController.generated.h"

class USPRespawnComponent;

UCLASS()
class STEAMPUNK_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASPPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USPRespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn *InPawn) override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(ESPMatchState State);
};
