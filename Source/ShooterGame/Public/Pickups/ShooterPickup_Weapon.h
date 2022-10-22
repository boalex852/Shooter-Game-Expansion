// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShooterPickup.h"
#include "ShooterPickup_Weapon.generated.h"

class AShooterWeapon;

UCLASS()
class SHOOTERGAME_API AShooterPickup_Weapon : public AShooterPickup
{
	GENERATED_UCLASS_BODY()
	
	/** check if pawn can use this pickup */
	virtual bool CanBePickedUp(AShooterCharacter* TestPawn) const override;

	virtual void EndPlay(EEndPlayReason::Type EndReason) override;

protected:

	/** The class of the weapon wickup.*/
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AShooterWeapon> WeaponClass;
	
	/** How much ammo in this weapon.*/
	UPROPERTY(BlueprintReadWrite)
	int32 Ammo = 0;

	/** How much currently ammo in the clip.*/
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmoInClip = 0;

	/** Indicates whether the pickup was taken or not.*/
	bool bPickedUp = false;

	/** The spawned weapon actor. */
	AShooterWeapon* SpawnedWeapon;

	/** After we recieve the weapon parameter, spawn it into the world.*/
	UFUNCTION(BlueprintCallable)
	void Initialization();

	/** Give pickup. */
	virtual void GivePickupTo(AShooterCharacter* Pawn) override;
};
