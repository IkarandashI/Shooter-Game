// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SPHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SPUtils.h"
#include "SPGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USPHealthComponent::USPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USPHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health,MaxHealth);
}

bool USPHealthComponent::TryToAddHealth(float HealthAmount)
{
    if(IsDead() || IsHealthFull()) return false;
    
    SetHealth(HealthAmount);
    return true;
}

void USPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USPHealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USPHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USPHealthComponent::OnTakeRadialDamage);
    }
}

void USPHealthComponent::OnTakePointDamage(AActor *DamagedActor, float Damage, AController *InstigatedBy, FVector HitLocation,
    UPrimitiveComponent *FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType *DamageType, AActor *DamageCauser)
{
    const auto PercievePawn = Cast<APawn>(DamagedActor);
    const auto AreEnemies = PercievePawn && SPUtils::AreEnemies(InstigatedBy, PercievePawn->Controller);
    if(AreEnemies)
    {
        const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor,BoneName);
        ApplyDamage(FinalDamage, InstigatedBy);
    }
}

void USPHealthComponent::OnTakeRadialDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, FVector Origin,
    FHitResult HitInfo, AController *InstigatedBy, AActor *DamageCauser)
{
    const auto PercievePawn = Cast<APawn>(DamagedActor);
    const auto AreEnemies = PercievePawn && SPUtils::AreEnemies(InstigatedBy, PercievePawn->Controller);
    if(AreEnemies)
    {
        ApplyDamage(Damage, InstigatedBy);
    }
}

void USPHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatedBy,
    AActor *DamageCauser)
{    
}

void USPHealthComponent::ApplyDamage(float Damage, AController *InstigatedBy)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USPHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
    ReportDamageEvent(Damage, InstigatedBy);
    PlayCameraShake();
}

void USPHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USPHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;
    
    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USPHealthComponent::PlayCameraShake()
{
    if(IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if(!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if(!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USPHealthComponent::Killed(AController *KillerController)
{
    if (!GetWorld()) return;
    
    const auto GameMode = Cast<ASPGameModeBase>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}

float USPHealthComponent::GetPointDamageModifier(AActor *DamagedActor, const FName &BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character ||
        !Character->GetMesh() ||
        !Character->GetMesh()->GetBodyInstance(BoneName)) return  1.f;

    const auto PhysMayerial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if(!PhysMayerial || !DamageModifiers.Contains(PhysMayerial)) return 1.f;

    return DamageModifiers[PhysMayerial];
}

void USPHealthComponent::ReportDamageEvent(float Damage, AController *InstigatedBy)
{
    if(!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;
    
    UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage,
        InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}
