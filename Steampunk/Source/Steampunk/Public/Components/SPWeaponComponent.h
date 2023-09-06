// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "SPCoreTypes.h"
#include "SPWeaponComponent.generated.h"


class ASPBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMPUNK_API USPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USPWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetWeaponUIData(FWeaponUIData& UIData) const;
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

    bool TryToAddAmmo(TSubclassOf<ASPBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<ASPBaseWeapon> WeaponType);

    void Zoom(bool Enabled);
    
protected:
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";
    
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ASPBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASPBaseWeapon*> Weapons;
        
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 WeaponIndex);

    int32 CurrentWeaponIndex = 0;

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;
    
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
         
    void SpawnWeapons();

    void AttachWeaponToSocket(ASPBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);


    bool CanReload() const;

    void OnEmptyClip(ASPBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
    
};