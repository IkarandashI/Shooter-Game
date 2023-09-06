// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

ASPPlayerCharacter::ASPPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CameraCollisionComponent"));
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASPPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(CameraCollisionComponent)

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASPPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASPPlayerCharacter::OnCameraCollisionEndOverlap);
}

void ASPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASPPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASPPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASPPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASPPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASPPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed,this, &ASPPlayerCharacter::OnStartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released,this, &ASPPlayerCharacter::OnStopSprint);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USPWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USPWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USPWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USPWeaponComponent::Reload);

    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool)
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &USPWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &USPWeaponComponent::Zoom, false);
}

void ASPPlayerCharacter::MoveForward(float Amount)
{
    IsMovimgForward = Amount > 0.f;
    if(Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASPPlayerCharacter::MoveRight(float Amount)
{
    if(Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASPPlayerCharacter::OnStartSprint()
{
    WantsToRun = true;
}

void ASPPlayerCharacter::OnStopSprint()
{
    WantsToRun = false;
}

void ASPPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    CheckCameraOverlap();
}

void ASPPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void ASPPlayerCharacter::CheckCameraOverlap()
{
    const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for (auto MeshChild :MeshChildren)
    {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChildGeometry)
        {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

bool ASPPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovimgForward && !GetVelocity().IsZero();
}

void ASPPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}


