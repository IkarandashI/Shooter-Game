// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAICharacter.h"
#include "AI/SPAIController.h"
#include "Components/SPAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/SPHealthBarWidget.h"
#include "Components/SPHealthComponent.h"


ASPAICharacter::ASPAICharacter(const FObjectInitializer &ObjInit)
  :Super(ObjInit.SetDefaultSubobjectClass<USPAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASPAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f,200.f,0.f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASPAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateHeathWidgetVisibility();
}

void ASPAICharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthWidgetComponent)
}

void ASPAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<USPHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if(!HealthBarWidget) return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASPAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto SPController = Cast<AAIController>(Controller);
    if (SPController && SPController->BrainComponent)
    {
        SPController->BrainComponent->Cleanup();
    }
}

void ASPAICharacter::UpdateHeathWidgetVisibility()
{
    if (!GetWorld() ||
        !GetWorld()->GetFirstPlayerController() ||
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
            return;
    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
