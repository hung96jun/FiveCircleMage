#include "Weapons/Magic/C_MagicSpawn.h"

AC_MagicSpawn::AC_MagicSpawn()
{
}

void AC_MagicSpawn::BeginPlay()
{
}

void AC_MagicSpawn::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	SpawnObject->Spawn(TargetPosition);

	// Show magic circle particle
	PlayParticle(MAIN_PARTICLE);
}