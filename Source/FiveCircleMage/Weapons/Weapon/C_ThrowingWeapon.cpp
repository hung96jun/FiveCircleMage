#include "Weapons/Weapon/C_ThrowingWeapon.h"
#include "Components/CapsuleComponent.h"

#include "Characters/C_Unit.h"

AC_ThrowingWeapon::AC_ThrowingWeapon()
{
	{
		Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
		RootComponent = Collision;

		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AC_ThrowingWeapon::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.Clear();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_ThrowingWeapon::OnBegin);
}

void AC_ThrowingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_ThrowingWeapon::OnFire(const FVector& Target)
{
	SetActive(true);

	Collision->SetSimulatePhysics(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision->AddImpulse(Target, NAME_None, true);

	CLog::DrawCapsule(GetWorld(), GetActorLocation(), 30.0f, 30.0f, FColor::Magenta, false, 10.0f);
}

void AC_ThrowingWeapon::SetActive(const bool Active)
{
	Super::SetActive(Active);
}

void AC_ThrowingWeapon::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	AC_Unit* other = Cast<AC_Unit>(OtherActor);
	if (other == nullptr) return;
	if (other->GetGenericTeamId() == OwnerActor->GetGenericTeamId()) return;

	DamageComp->GiveDmg(OtherActor, Damage, DebuffType);

	OnHitAction();
}
