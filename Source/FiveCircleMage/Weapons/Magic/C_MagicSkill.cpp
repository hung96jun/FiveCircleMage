#include "Weapons/Magic/C_MagicSkill.h"
#include "Global.h"
#include "Particles/ParticleSystem.h"
#include "Components/C_DamageComponent.h"
#include "Components/CapsuleComponent.h"

AC_MagicSkill::AC_MagicSkill()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
}

void AC_MagicSkill::BeginPlay()
{
	Super::BeginPlay();
}

void AC_MagicSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Duration -= DeltaTime;
}

void AC_MagicSkill::SetMagic(UParticleSystem* CopyMainParticle, UParticleSystem* CopyEndParticle, float Dmg, float LifeTime, EUnitState MagicProperty, float Speed)
{
	// ÀÌÆåÆ® ¼³Á¤
	MainParticle = CopyMainParticle;
	EndParticle = CopyEndParticle;

	Damage = Dmg;
	State = MagicProperty;
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
	FTransform transform;
	transform.SetLocation(GetActorLocation());
	transform.SetRotation(GetActorRotation().Quaternion());

	if(ParticleType == MAIN_PARTICLE)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MainParticle, transform);
	else if(ParticleType == END_PARTICLE && EndParticle != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EndParticle, transform);
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
