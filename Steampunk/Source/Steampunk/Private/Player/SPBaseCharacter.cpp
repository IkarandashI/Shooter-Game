// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPBaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SPCharacterMovementComponent.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ASPBaseCharacter::ASPBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
    
    HealthComponent = CreateDefaultSubobject<USPHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USPWeaponComponent>("WeaponComponent");
}

void ASPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &ASPBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASPBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASPBaseCharacter::OnGroundLanded);
    
}

void ASPBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
}

void ASPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASPBaseCharacter::IsRunning() const
{
    return false;
}

float ASPBaseCharacter::GetMovementDirection() const
{
    if(GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees: Degrees * FMath::Sign(CrossProduct.Z);
}

void ASPBaseCharacter::OnDeath()
{
    // PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASPBaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASPBaseCharacter::SetPlayerColor(const FLinearColor &Color)
{
    const auto MaterialInst = GetMesh()->CreateDynamicMaterialInstance(0);
    if(!MaterialInst) return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}