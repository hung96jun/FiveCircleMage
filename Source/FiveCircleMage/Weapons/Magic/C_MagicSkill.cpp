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

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_MagicSkill::OnBeginOverlap);
}

void AC_MagicSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_MagicSkill::SetMagic(UParticleSystem* CopyParticle, FVector3d CollisionScale, float Dmg, EUnitState MagicProperty, float Speed)
{
	// ÀÌÆåÆ® ¼³Á¤
	Particle = CopyParticle;

	Collision->SetRelativeScale3D(CollisionScale);
	Damage = Dmg;
	State = MagicProperty;
	MoveSpeed = Speed;
}

void AC_MagicSkill::SetCollisionSize(FVector3d CollisionSize)
{
	Collision->SetRelativeScale3D(CollisionSize);
}

void AC_MagicSkill::PlayParticle()
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());
	transform.SetRotation(GetActorRotation().Quaternion());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, transform);
}

void AC_MagicSkill::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == this) return;
	if (OtherActor == OwnerActor) return;

	AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);

	if (otherUnit->GetForceType() == OwnerActor->GetForceType()) return;

	DamageComp->GiveDmg(OtherActor, Damage, State);
}