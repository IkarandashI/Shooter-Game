// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SPNextLocationTask.generated.h"

UCLASS()
class STEAMPUNK_API USPNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
    USPNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector AimLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    bool SelfCenter = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (EditCondition = "!SelfCenter"))
    FBlackboardKeySelector CenterActorKey;
};
