// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPBasePickup.generated.h"

class USphereComponent;

UCLASS()
class STEAMPUNK_API ASPBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	ASPBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category="Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Pickup")
    float RespawnTime = 5.f;
        
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

public:

	virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    float RotationYaw = 0.f;
    FTimerHandle RespawnTimerHandle;
    
    virtual bool GivePickupTo(APawn* PlayerPawn);
    
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
