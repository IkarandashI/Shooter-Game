// Fill out your copyright notice in the Description page of Project Settings.


#include "SPDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASPDevDamageActor::ASPDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ASPDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASPDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {},this, nullptr, DoFullDamage);
}

