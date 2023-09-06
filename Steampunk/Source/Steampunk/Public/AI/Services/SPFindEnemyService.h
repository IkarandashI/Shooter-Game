// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SPFindEnemyService.generated.h"


UCLASS()
class STEAMPUNK_API USPFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
    USPFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
};
