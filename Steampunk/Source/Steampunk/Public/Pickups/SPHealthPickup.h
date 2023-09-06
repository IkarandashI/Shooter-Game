// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SPBasePickup.h"
#include "SPHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class STEAMPUNK_API ASPHealthPickup : public ASPBasePickup
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin = "1.0", ClampMax = "100.0"))
    int32 HealthAmount = 100;
    
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
