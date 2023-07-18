#pragma once

#include "CoreMinimal.h"
#include "Weapons/C_DamageBase.h"
#include "C_MagicSkill.generated.h"

class UCapsuleComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_MagicSkill : public AC_DamageBase
{
	GENERATED_BODY()

protected:
	// Particle
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particle")
		FString Key;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCapsuleComponent* Collision = nullptr;

public:
	AC_MagicSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void SetMagic(UParticleSystem* CopyMainParticle, UParticleSystem* CopyEndParticle, float Dmg, float LifeTime = 5.0f, EUnitState MagicProperty = EUnitState::Normal, float Speed = 0.0f);
	void SetCollision(FVector3d CollisionSize, FRotator Rotation);

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) {};
	
	void PlayParticle(int32 ParticleType = MAIN_PARTICLE);

protected:
	void SetCastingRotation(FRotator Rotation);
	
protected:
	float OriginDuration;
	float Duration;
	float MoveSpeed;

	UParticleSystem* MainParticle = nullptr;
	UParticleSystem* EndParticle = nullptr;

	EUnitState State;
};