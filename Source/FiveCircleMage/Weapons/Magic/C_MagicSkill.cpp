#include "Weapons/Magic/C_MagicSkill.h"
#include "Global.h"
#include "Particles/ParticleSystem.h"
#include "Components/C_DamageComponent.h"
#include "Components/CapsuleComponent.h"

AC_MagicSkill::AC_MagicSkill()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	ActiveCollision(false);
}

void AC_MagicSkill::BeginPlay()
{
	Super::BeginPlay();
}

void AC_MagicSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Duration -= DeltaTime;

	if (Duration <= 0.0f)
		ActiveCollision(false);
}

void AC_MagicSkill::SetMagic(UNiagaraSystem* CopyMainParticle, FVector CopyMainLocation, FRotator CopyMainRotation,
							 UNiagaraSystem* CopyEndParticle, FVector CopyEndLocation, FRotator CopyEndRotation, 
							 float Dmg, ESkillType Type, float LifeTime, EUnitState MagicProperty, float Speed)
{
	MainParticle.SetParticle(CopyMainParticle, CopyMainLocation, CopyMainRotation);
	EndParticle.SetParticle(CopyEndParticle, CopyEndLocation, CopyEndRotation);

	Damage = Dmg;
	State = MagicProperty;
	MagicType = Type;
	MoveSpeed = Speed;
	OriginDuration = LifeTime;
}

void AC_MagicSkill::SetCollision(FVector3d CollisionSize, FRotator Rotation)
{
	Collision->SetRelativeScale3D(CollisionSize);
	Collision->SetRelativeRotation(Rotation);
}

void AC_MagicSkill::PlayParticle(int32 ParticleType)
{
	if (ParticleType == MAIN_PARTICLE)
		MainParticle.Play(Collision);
	else if (ParticleType == END_PARTICLE && EndParticle.IsActive())
		EndParticle.Play(Collision);
}

void AC_MagicSkill::SetCastingRotation(FRotator Rotation)
{
	FRotator TmpRotation = GetActorRotation();

	if (Rotation.Pitch != 0.0f)
		TmpRotation.Pitch = Rotation.Pitch;

	if (Rotation.Yaw != 0.0f)
		TmpRotation.Yaw = Rotation.Yaw;

	if (Rotation.Roll != 0.0f)
		TmpRotation.Roll = Rotation.Roll;

	SetActorRotation(TmpRotation);
}

bool AC_MagicSkill::IsOtherActor(AActor* OtherActor)
{
	if (OtherActor == nullptr) return false;
	if (OtherActor == this) return false;
	if (OtherActor == OwnerActor) return false;

	AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);

	if (otherUnit == nullptr) return false;
	if (otherUnit->GetForceType() == OwnerActor->GetForceType()) return false;

	return true;
}

bool AC_MagicSkill::IsOtherActor(AActor* OtherActor, AC_Unit*& CastedOtherActor)
{
	if (OtherActor == nullptr) return false;
	if (OtherActor == this) return false;
	if (OtherActor == OwnerActor) return false;

	CastedOtherActor = Cast<AC_Unit>(OtherActor);

	if (CastedOtherActor == nullptr) return false;
	if (CastedOtherActor->GetForceType() == OwnerActor->GetForceType()) return false;

	return true;
}