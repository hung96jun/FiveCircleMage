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
/// 6. Mes
///		- VampiricAreaSkill: void SetInterval(float IntervalTime)
/// 
///-----------------------------------------------------------------------------------------

#include "CoreMinimal.h"
#include "Weapons/C_DamageBase.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Enums/C_SkillType.h"
#include "C_MagicSkill.generated.h"

class UCapsuleComponent;

struct FParticleInfo
{
public:
	void SetParticle(UNiagaraSystem* _Particle, FVector _Location, FRotator _Rotation)
	{
		Particle = _Particle;
		Location = _Location;
		Rotation = _Rotation;
	}

	void Play(UCapsuleComponent*& Collision)
	{
		if (Particle == nullptr)
		{
			CLog::Print("Particle is nullptr!!!");
			return;
		}

		if (Collision == nullptr)
		{
			CLog::Print("Collision is nullptr!!");
			return;
		}

		Comp = UNiagaraFunctionLibrary::SpawnSystemAttached(Particle, Collision, L"None", Location, Rotation,
			EAttachLocation::KeepRelativeOffset, true);
		Comp->ResetSystem();
		Comp->SetVisibility(true);
	}

	void Stop()
	{
		Comp->SetPaused(true);
		Comp->SetVisibility(false);
	}

	const bool IsActive() { return Particle != nullptr; }
	UNiagaraComponent*& GetComp() { return Comp; }

private:
	UNiagaraComponent* Comp = nullptr;
	UNiagaraSystem* Particle = nullptr;

	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
};

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
	void SetMagic(UNiagaraSystem* CopyMainParticle, FVector CopyMainLocation, FRotator CopyMainRotation,
		UNiagaraSystem* CopyEndParticle, FVector CopyEndLocation, FRotator CopyEndRotation,
		float Dmg, ESkillType Type, float LifeTime = 5.0f, EUnitState MagicProperty = EUnitState::Normal, float Speed = 0.0f);
	void SetCollision(FVector3d CollisionSize, FRotator Rotation);
	void SetCollisionRadius(float Radius) { Collision->SetCapsuleRadius(Radius); }
	void SetCollisionHeight(float HalfHeight) { Collision->SetCapsuleHalfHeight(HalfHeight); }

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) {};

	virtual void PlayParticle(int32 ParticleType = MAIN_PARTICLE);

	const ESkillType& GetMagicType() { return MagicType; }

	void SetOriginRotation(FRotator Rot) { OriginRot = Rot; }

protected:
	void SetCastingRotation(FRotator Rotation);

	bool IsOtherActor(AActor* OtherActor);
	bool IsOtherActor(AActor* OtherActor, AC_Unit*& CastedOtherActor);

	void ActiveCollision(bool Active) { Active ? Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly) : Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision); }

protected:
	float OriginDuration;
	float Duration;
	float MoveSpeed;

	FParticleInfo MainParticle;
	FParticleInfo EndParticle;

	EUnitState State;
	ESkillType MagicType;

	FRotator OriginRot;
};