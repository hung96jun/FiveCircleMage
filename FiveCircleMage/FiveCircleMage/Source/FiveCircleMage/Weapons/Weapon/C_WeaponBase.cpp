#include "Weapons/Weapon/C_WeaponBase.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

AC_WeaponBase::AC_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_WeaponBase::Spawn()
{
	
}
