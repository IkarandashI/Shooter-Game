// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPProjectile.generated.h"

class USPWeaponFXComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class STEAMPUNK_API ASPProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASPProjectile();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleAnywhere, Category="Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category="Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, Category="VFX")
    USPWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
    float DamageRadius = 200.f;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
    float DamageAmount = 50.f;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
    bool DoFullDamage = false;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
    float LifeSeconds = 5.f;
    
	virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

    AController* GetController() const;
};
