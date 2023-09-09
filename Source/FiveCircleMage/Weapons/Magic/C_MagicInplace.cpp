#include "Weapons/Magic/C_MagicInplace.h"

AC_MagicInplace::AC_MagicInplace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_MagicInplace::BeginPlay()
{
	Super::BeginPlay();
	Collision->SetCapsuleHalfHeight(300.0f);
	OriginRadius = Collision->GetUnscaledCapsuleRadius();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_MagicInplace::OnBeginOverlap);
}

void AC_MagicInplace::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsOtherActor(OtherActor) == false) return;

	DamageComp->GiveDmg(OtherActor, Damage, State);
}

void AC_MagicInplace::Tick(float DeltaTime)
{
	if (bActive == false) return;
	if (Duration < 0.0f) return;

	Super::Tick(DeltaTime);

	Spreading(DeltaTime);
}

void AC_MagicInplace::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;
	Collision->SetCapsuleRadius(OriginRadius);

	SetCastingRotation(Rotation);

	SetActorLocation(CasterPosition);

	PlayParticle(MAIN_PARTICLE);

	ActiveCollision(true);
}

void AC_MagicInplace::Spreading(float DeltaTime)
{
	float radius = Collision->GetUnscaledCapsuleRadius();

	if (radius > MaxRadius)
	{
		ActiveCollision(false);
		bActive = false;
		return;
	}

	radius += SpreadSpeed * DeltaTime;
	Collision->SetCapsuleRadius(radius);
}