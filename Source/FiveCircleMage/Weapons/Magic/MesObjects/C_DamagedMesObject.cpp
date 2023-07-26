#include "Weapons/Magic/MesObjects/C_DamagedMesObject.h"

#include "Characters/C_Unit.h"

AC_DamagedMesObject::AC_DamagedMesObject()
{

}

void AC_DamagedMesObject::BeginPlay()
{
	Super::BeginPlay();

}

void AC_DamagedMesObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_DamagedMesObject::EndActive()
{
	Super::EndActive();

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
}
