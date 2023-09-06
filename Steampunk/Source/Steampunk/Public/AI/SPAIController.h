// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SPAIController.generated.h"

class USPAIPerceptionComponent;
class USPRespawnComponent;

UCLASS()
class STEAMPUNK_API ASPAIController : public AAIController
{
	GENERATED_BODY()
public:
    ASPAIController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USPAIPerceptionComponent* SPAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USPRespawnComponent* RespawnComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FName FocusOnKeyName = "EnemyActor";
    
    virtual void OnPossess(APawn *InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor() const;
};
