// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SPBaseCharacter.h"
#include "SPAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class STEAMPUNK_API ASPAICharacter : public ASPBaseCharacter
{
	GENERATED_BODY()

public:
    ASPAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    UBehaviorTree* BehaviorTreeAsset;

    virtual void Tick(float DeltaSeconds) override;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    float HealthVisibilityDistance = 1000.0f;
    
    virtual void BeginPlay() override;
    
    virtual void OnHealthChanged(float Health, float HealthDelta) override;
    virtual void OnDeath() override;

private:
    void UpdateHeathWidgetVisibility();
};
