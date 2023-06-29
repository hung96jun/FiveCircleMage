#include "Weapons/C_WeaponBase.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

#include "Components/C_DamageComponent.h"

AC_WeaponBase::AC_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	{
		DamageComp = CreateDefaultSubobject<UC_DamageComponent>("DamageComponent");
	}
}

void AC_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
