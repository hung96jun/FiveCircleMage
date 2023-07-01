#include "Characters/C_Unit.h"


AC_Unit::AC_Unit()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_Unit::BeginPlay()
{
	Super::BeginPlay();

}

void AC_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Unit::GetDmg(const float Dmg, const EUnitState Type)
{
	
}
