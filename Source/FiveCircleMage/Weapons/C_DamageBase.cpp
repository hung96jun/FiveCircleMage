#include "Weapons/C_DamageBase.h"

#include "Components/C_DamageComponent.h"


AC_DamageBase::AC_DamageBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	{
		DamageComp = CreateDefaultSubobject<UC_DamageComponent>("DamageComponent");
	}
}

void AC_DamageBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AC_DamageBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

