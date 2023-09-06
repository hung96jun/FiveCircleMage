#include "Weapons/Weapon/C_WeaponBase.h"
#include "Engine/StaticMesh.h"
//#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstance.h"
#include "Global.h"

AC_WeaponBase::AC_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Collision->SetCollisionProfileName(L"Weapon");
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

	if (bActive == false) return;

	FString temp = L"";
	temp += L"CollisionEnabled : ";
	switch (Collision->GetCollisionEnabled())
	{	
	case ECollisionEnabled::NoCollision:
		temp += L"NoCollision";
		break;
	case ECollisionEnabled::QueryOnly:
		temp += L"QueryOnly";
		break;
	case ECollisionEnabled::PhysicsOnly:
		temp += L"PhysicsOnly";
		break;
	case ECollisionEnabled::QueryAndPhysics:
		temp += L"QueryAndPhysics";
		break;
	case ECollisionEnabled::ProbeOnly:
		temp += L"ProbeOnly";
		break;
	case ECollisionEnabled::QueryAndProbe:
		temp += L"QueryAndProbe";
		break;
	}

	CLog::Print(temp, 0.01f, FColor::Cyan);
}

void AC_WeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
	{
		CLog::Print(L"WeaponBase - OnBeginOverlap, OtherActor == nullptr", 10.0f, FColor::Red);
		return;
	}
	if (OtherActor == this) 
	{
		CLog::Print(L"WeaponBase - OnBeginOverlap, OtherActor == this", 10.0f, FColor::Red);
		return;
	}
	if (OtherActor == OwnerActor) 
	{
		CLog::Print(L"WeaponBase - OnBeginOverlap, OtherActor == OwnerActor", 10.0f, FColor::Red);
		return;
	}

	FString temp = L"";
	temp += L"OtherActor - " + OtherActor->GetActorLabel();
	temp += L"\nDamage - " + FString::SanitizeFloat(Damage);
	CLog::Print(temp, 10.0f, FColor::Red);

	DamageComp->GiveDmg(OtherActor, Damage);
}

void AC_WeaponBase::SetActive(const bool Active)
{
	Super::SetActive(Active);

	//if (bActive == false)
	//	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//else
	//	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AC_WeaponBase::SetBoxExtent(const FVector Value)
{
	Collision->SetBoxExtent(Value);
}

void AC_WeaponBase::SetCollisionEnabled(ECollisionEnabled::Type Type)
{
	Super::SetCollisionEnabled(Type);

	Collision->SetCollisionEnabled(Type);
}
