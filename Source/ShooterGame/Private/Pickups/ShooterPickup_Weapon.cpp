// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "ShooterWeapon.h"
#include "Pickups/ShooterPickup_Weapon.h"

AShooterPickup_Weapon::AShooterPickup_Weapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

bool AShooterPickup_Weapon::CanBePickedUp(AShooterCharacter* TestPawn) const
{
	//Any alive player can pick up the weapon.
	if (TestPawn->IsAlive())
	{
		return true;
	}

	return true;
}

void AShooterPickup_Weapon::Initialization()
{
	//Spawn the weapon, make sure the weapon class is valid and not zero ammo.
	if (IsValid(WeaponClass) && Ammo > 0)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnedWeapon = GetWorld()->SpawnActor<AShooterWeapon>(WeaponClass, SpawnInfo);
		SpawnedWeapon->SetAmmo(Ammo);
		SpawnedWeapon->SetAmmoInClip(CurrentAmmoInClip);
	}	
}

void AShooterPickup_Weapon::GivePickupTo(AShooterCharacter* Pawn)
{
	//Add the weapon to the specified player.
	Pawn->AddWeapon(SpawnedWeapon);
}
