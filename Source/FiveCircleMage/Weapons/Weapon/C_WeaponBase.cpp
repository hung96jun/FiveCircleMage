#include "Weapons/Weapon/C_WeaponBase.h"
#include "Engine/StaticMesh.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstance.h"
#include "Global.h"

AC_WeaponBase::AC_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	RootComponent = Collision;
}

void AC_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_WeaponBase::OnBeginOverlap);

	SetActive(false);
}

void AC_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_WeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == this) return;
	if (OtherActor == OwnerActor) return;

	DamageComp->GiveDmg(OtherActor, Damage);
}

void AC_WeaponBase::SetActive(const bool Active)
{
	Super::SetActive(Active);

	if (bActive == false)
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	else
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
