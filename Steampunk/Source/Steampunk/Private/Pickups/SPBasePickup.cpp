// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/SPBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASPBasePickup::ASPBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASPBasePickup::BeginPlay()
{
	Super::BeginPlay();
    check(CollisionComponent);
    GenerateRotationYaw();
}

void ASPBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.f, RotationYaw, 0.f));
}



void ASPBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

bool ASPBasePickup::GivePickupTo(APawn *PlayerPawn)
{
    return false;
}

void ASPBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if(GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }
    
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASPBasePickup::Respawn, RespawnTime);
}

void ASPBasePickup::Respawn()
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if(GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ASPBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.f : -1.f;
    RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}

bool ASPBasePickup::CouldBeTaken() const
{
    return GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}