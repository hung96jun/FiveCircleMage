#include "Weapons/Magic/C_MagicMissile.h"

AC_MagicMissile::AC_MagicMissile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_MagicMissile::BeginPlay()
{
	Super::BeginPlay();
}

void AC_MagicMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AC_MagicMissile::Move(float DeltaTime)
{
	FVector Location = GetActorLocation() + MoveSpeed * MoveDirection * DeltaTime;

	SetActorLocation(Location);
}