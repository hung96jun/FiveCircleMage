#include "Weapons/Magic/C_MagicCoord.h"

AC_MagicCoord::AC_MagicCoord()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_MagicCoord::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_MagicCoord::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AC_MagicCoord::OnEndOverlap);
}

void AC_MagicCoord::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == this) return;
	if (OtherActor == OwnerActor) return;

	AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);

	if (otherUnit->GetForceType() == OwnerActor->GetForceType()) return;

	if (DelayTime < 0.0f) return;

	Targets.Add(otherUnit);
}

void AC_MagicCoord::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == this) return;
	if (OtherActor == OwnerActor) return;
	
	AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);
	if (otherUnit->GetForceType() == OwnerActor->GetForceType()) return;

	Targets.Remove(otherUnit);
}

void AC_MagicCoord::Tick(float DeltaTime)
{
	if (bActive == false) return;
	if (Duration < 0.0f) { bActive = false; return; }

	Super::Tick(DeltaTime);


	if (DelayTime > 0.0f)
	{
		DelayTime -= DeltaTime;
	}
	else if (Targets.Num() > 0)
	{
		for (AC_Unit* unit : Targets)
		{
			DamageComp->GiveDmg(unit, Damage, State);
		}

		Targets.Empty();
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (EndParticle != nullptr)
			PlayParticle(END_PARTICLE);
	}
}

void AC_MagicCoord::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;
	DelayTime = OriginDelayTime;
	Targets.Empty();

	SetCastingRotation(Rotation);

	SetActorLocation(TargetPosition);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	PlayParticle(MAIN_PARTICLE);

	if (Duration < DelayTime)
		Duration = DelayTime + 1.0f;
}