#include "Weapons/Magic/C_MagicBeam.h"

AC_MagicBeam::AC_MagicBeam()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision->SetHiddenInGame(false);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetCollisionProfileName(L"Magic");
	Capsule->SetCapsuleHalfHeight(1.0f);
	Capsule->SetCapsuleRadius(1.0f);
}

void AC_MagicBeam::BeginPlay()
{
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_MagicBeam::OnBeginOverlap);
}

void AC_MagicBeam::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsOtherActor(OtherActor) == false) return;

	DamageComp->GiveDmg(OtherActor, Damage, State);
}

void AC_MagicBeam::Tick(float DeltaTime)
{
	if (bActive == false) return;
	if (Duration < 0.0f)
	{
		bActive = false;
		ActiveCollision(false);
		MainParticle.Stop();
		EndParticle.Stop();

		return;
	}

	Super::Tick(DeltaTime);
}

void AC_MagicBeam::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;

	SetCastingRotation(Rotation);

	SetActorLocation(CasterPosition);

	PlayParticle(MAIN_PARTICLE);
	PlayParticle(END_PARTICLE);

	ActiveCollision(true);
	SetBeamPosition(CasterPosition, Rotation);
}

void AC_MagicBeam::PlayParticle(int32 ParticleType)
{
	if (ParticleType == MAIN_PARTICLE)
		MainParticle.Play(Capsule);
	else if (ParticleType == END_PARTICLE && EndParticle.IsActive())
		EndParticle.Play(Capsule);
	else if (ParticleType == SUB_PARTICLE && SubParticle.IsActive())
		SubParticle.Play(Capsule);
}

void AC_MagicBeam::SetBeamPosition(FVector CasterLocation, FRotator CasterRotation)
{
	FVector farFromCaster = GetActorForwardVector() * 100.0f;

	FVector location = GetActorLocation() + farFromCaster + GetActorForwardVector() * Collision->GetScaledCapsuleHalfHeight();
	FRotator rotation = GetActorRotation() + FRotator(-90, 0, 0);

	Collision->SetRelativeLocation(location);
	Collision->SetRelativeRotation(rotation);

	Capsule->SetRelativeLocation(CasterLocation + farFromCaster);
	Capsule->SetRelativeRotation(CasterRotation);
}