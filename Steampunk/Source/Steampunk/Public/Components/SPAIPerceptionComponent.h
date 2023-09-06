// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SPAIPerceptionComponent.generated.h"


UCLASS()
class STEAMPUNK_API USPAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
    AActor* GetClosesEnemy() const;
};
