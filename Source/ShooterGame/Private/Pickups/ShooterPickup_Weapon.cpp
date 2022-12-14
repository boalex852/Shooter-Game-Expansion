// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "ShooterWeapon.h"
#include "Pickups/ShooterPickup_Weapon.h"

AShooterPickup_Weapon::AShooterPickup_Weapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

bool AShooterPickup_Weapon::CanBePickedUp(AShooterCharacter* TestPawn) const
{
	//Any alive player, with enough space in inventory, can pick up the weapon.
	if (TestPawn->IsAlive() && TestPawn->GetInventoryCount() < TestPawn->GetMaxWeaponsCount())
	{
		return true;
	}

	return false;
}

void AShooterPickup_Weapon::EndPlay(EEndPlayReason::Type EndReason)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		//If no one picked up the weapon and its valid, destroy it. Notice it only spawns on server side.
		if (!bPickedUp && IsValid(SpawnedWeapon))
		{
			SpawnedWeapon->Destroy();
		}
	}

	Super::EndPlay(EndReason);
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
	//Weapon was picked up.
	bPickedUp = true;
}
