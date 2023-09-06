// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPBaseCharacter.generated.h"


class USPHealthComponent;
class USPWeaponComponent;

UCLASS()
class STEAMPUNK_API ASPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPBaseCharacter(const FObjectInitializer& ObjInit);

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USPHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USPWeaponComponent* WeaponComponent;

    UPROPERTY(EditAnywhere, Category="Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditAnywhere, Category="Damage")
    float LifeSpanOnDeath = 5.0f;

    UPROPERTY(EditAnywhere, Category="Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditAnywhere, Category="Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(EditAnywhere, Category="Material")
    FName MaterialColorName = "Paint Color";

    virtual void OnDeath();
	virtual void BeginPlay() override;

    virtual void OnHealthChanged(float Health, float HealthDelta);

public:	
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category="Movement")
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& Color);
        
private:    
    

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};


