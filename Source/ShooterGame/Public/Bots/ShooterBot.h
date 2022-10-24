// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ShooterCharacter.h"
#include "ShooterBot.generated.h"

UCLASS()
class AShooterBot : public AShooterCharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Behavior)
	class UBehaviorTree* BotBehavior;

	/**The current bot controller possing the pawn.*/
	UPROPERTY()
	AController* BotController;

	virtual bool IsFirstPerson() const override;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	/** Handle bot receiving damage.*/
	virtual void DamageToBot(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser) override;

	/** Handle bot freeze damage.*/
	void Freeze();

	/** Unfreeze bot. Called when freeze actor destroyed.*/
	UFUNCTION()
	void Unfreeze(AActor* DestroyedActor);

	/** Adjust the enemy parameters on bot.*/
	virtual bool IsEnemyFor(AController* TestPC) const override;

	/** Handle bot shrinking.*/
	void Shrink();

	/** Handle bot unshrinking. Called when shrink actor destroyed.*/
	UFUNCTION()
	void Unshrink(AActor* DestroyedActor);
};