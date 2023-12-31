// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "C_MagicBeam.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_MagicBeam : public AC_MagicSkill
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UCapsuleComponent* Capsule = nullptr;

protected:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndBeam();

public:
	AC_MagicBeam();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

	virtual void PlayParticle(int32 ParticleType = MAIN_PARTICLE) override;

	void SetSubParticle(UNiagaraSystem* Particle, FVector Location, FRotator Rotation) { SubParticle.SetParticle(Particle, Location, Rotation); }

private:
	void SetBeamPosition(FVector CasterLocation, FRotator CasterRotation);

private:
	FParticleInfo SubParticle;

	FTimerHandle EndTimerHandle;
	FTimerDelegate EndTimerDelegate;
};
