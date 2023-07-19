#pragma once

///----------------------MagicSkill required setting per child classes----------------------
/// 
/// =Common Setting=
///		- SetMagic(Main particle, End particle, damage, Max duration for effect(Not essential),
///				  Magic debuff property(Not essential), Particle move speed(Not essential))
///		- SetCollision(Collision scale, Collision rotation)
/// 
/// 1. Missile
///		- Nothing
/// 
/// 2. Coord
///		- SetDelayTime(Delay time for damaging)
/// 
/// 3. Spawn
///		- Nothing
/// 
/// 4. Inplace
///		- void SetMaxRadius(Radius of capsule collision)
///		- void SetSpreadSpeed(speed of increasing collision radius)
/// 
/// 5. Beam
///		- Nothing
/// 
///-----------------------------------------------------------------------------------------

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
	
	virtual void PlayParticle(int32 ParticleType = MAIN_PARTICLE);

protected:
	void SetCastingRotation(FRotator Rotation);
	
	bool IsOtherActor(AActor* OtherActor);
	bool IsOtherActor(AActor* OtherActor, AC_Unit*& CastedOtherActor);

	void ActiveCollision(bool Active) { Active ? Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly) : Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);}

protected:
	float OriginDuration;
	float Duration;
	float MoveSpeed;

	UParticleSystem* MainParticle = nullptr;
	UParticleSystem* EndParticle = nullptr;

	EUnitState State;
};