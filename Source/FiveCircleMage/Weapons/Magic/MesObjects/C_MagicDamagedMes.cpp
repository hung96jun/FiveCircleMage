#include "Weapons/Magic/MesObjects/C_MagicDamagedMes.h"

#include "Characters/C_Unit.h"

AC_MagicDamagedMes::AC_MagicDamagedMes()
{

}

void AC_MagicDamagedMes::BeginPlay()
{
	Super::BeginPlay();

}

void AC_MagicDamagedMes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_MagicDamagedMes::EndActive()
{
	Super::EndActive();

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
}
