#include "Weapons/Magic/MesObjects/C_MagicMes.h"

AC_MagicMes::AC_MagicMes()
{
	PrimaryActorTick.bCanEverTick = true;

	bActive = false;
}

void AC_MagicMes::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_MagicMes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Duration < 0.0f)
		EndActive();
}

void AC_MagicMes::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	MoveSpeed = 0.0f;
	Duration = OriginDuration;

	SetActorLocation(TargetPosition);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	PlayParticle(MAIN_PARTICLE);
}

void AC_MagicMes::EndActive()
{
	bActive = false;

	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
