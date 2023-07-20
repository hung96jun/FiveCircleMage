#include "Weapons/Magic/MesObjects/C_MesObject.h"

AC_MesObject::AC_MesObject()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_MesObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_MesObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Duration < 0.0f)
		EndActive();
}

void AC_MesObject::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	MoveSpeed = 0.0f;
	Duration = OriginDuration;

	SetActorLocation(TargetPosition);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	PlayParticle(MAIN_PARTICLE);
}

void AC_MesObject::EndActive()
{
	bActive = false;

	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
