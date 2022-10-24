// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Bots/ShooterBot.h"
#include "Bots/ShooterAIController.h"
#include "ShooterDamageType.h"

AShooterBot::AShooterBot(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AIControllerClass = AShooterAIController::StaticClass();

	UpdatePawnMeshes();

	bUseControllerRotationYaw = true;
}

bool AShooterBot::IsFirstPerson() const
{
	return false;
}

void AShooterBot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

void AShooterBot::DamageToBot(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	UShooterDamageType* DamageType = Cast<UShooterDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());
	if (DamageType->bFreezeEffect && IsValid(FreezeActorClass))
	{
		//Freeze bot if damage is of freeze type.
		Freeze();
	}
}

void AShooterBot::Freeze()
{
	//If bot already has an active effect, do nothing.
	if (bIsAnyEffectActive_Server)
	{
		return;
	}

	//Get the bot controller and unposses this pawn (stop logic).
	BotController = GetController();
	checkf(IsValid(BotController), TEXT("Bot has no controller, critical failure"));
	BotController->UnPossess();
	//Stop weapons from firing.
	StopWeaponFire();

	//Spawn the freeze actor.
	FreezeActor = SpawnAndAttachActor(FreezeActorClass, this, FreezeTime);
	FreezeActor->OnDestroyed.AddDynamic(this, &AShooterBot::Unfreeze);
	//Bot currently frozen.
	bIsAnyEffectActive_Server = true;
}

void AShooterBot::Unfreeze(AActor* DestroyedActor)
{
	//Reposses this pawn.
	BotController->Possess(this);
	//Bot no longer frozen.
	bIsAnyEffectActive_Server = false;
}

bool AShooterBot::IsEnemyFor(AController* TestPC) const
{
	//If any effect is on the bot, it might be frozen, thus unpossed.
	//We don't want other bots to shoot during the freeze period at this pawn.
	if (bIsAnyEffectActive_Server)
	{
		return false;
	}

	return Super::IsEnemyFor(TestPC);
}
