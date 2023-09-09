#include "Weapons/Weapon/C_ThrowingWeapon.h"
#include "Components/CapsuleComponent.h"

#include "Characters/C_Unit.h"

AC_ThrowingWeapon::AC_ThrowingWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	{
		Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
		RootComponent = Collision;

		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Collision->SetCollisionProfileName(L"Magic");
	}
}

void AC_ThrowingWeapon::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.Clear();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_ThrowingWeapon::OnBegin);
	Collision->OnComponentHit.AddDynamic(this, &AC_ThrowingWeapon::OnHit);
}

void AC_ThrowingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -900 : 최소 높이
	if (GetActorLocation().Z <= -900.0f)
		OnHitAction();
}

void AC_ThrowingWeapon::OnFire(const FVector& Target, AC_Unit* Actor)
{
	SetActive(true);
	SetOwnerActor(Actor);

	Collision->SetSimulatePhysics(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Collision->AddImpulse(Target, NAME_None, true);

	Velocity = Target;

	CLog::DrawCapsule(GetWorld(), GetActorLocation(), 30.0f, 30.0f, FColor::Magenta, false, 10.0f);
}

void AC_ThrowingWeapon::OnHitAction()
{
	SetActive(false);
	SetActorLocation(FVector::ZeroVector);
	Collision->SetSimulatePhysics(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Velocity = FVector::ZeroVector;
	SetOwnerActor(nullptr);
	SetActorHiddenInGame(true);
}

void AC_ThrowingWeapon::SetActive(const bool Active)
{
	Super::SetActive(Active);
}

void AC_ThrowingWeapon::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OwnerActor == nullptr) return;
	if (OtherActor == OwnerActor) return;


	AC_Unit* other = Cast<AC_Unit>(OtherActor);
	if (other == nullptr)
	{
		FString temp = L"";
		AStaticMeshActor* test = Cast<AStaticMeshActor>(OtherActor);
		if (test == nullptr)
			CLog::Print(L"ThrowingWeapon Test Failed", 10.0f, FColor::Red);
		else
			CLog::Print(L"ThrowingWeapon Test Success", 10.0f, FColor::Green);

		return;
	}
	if (other->GetGenericTeamId() == OwnerActor->GetGenericTeamId()) return;

	FString temp = L"ThrowingWeapon - OnHit, " + other->GetActorLabel();
	temp += L", Damage : " + FString::SanitizeFloat(Damage);
	CLog::Print(temp, 10.0f, FColor::Magenta);
	 
	DamageComp->GiveDmg(OtherActor, Damage, DebuffType);

	OnHitAction();
}

void AC_ThrowingWeapon::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CLog::Print(L"ThrowingWeapon OnHit", 10.0f, FColor::Red);

	//if (OtherActor == nullptr) return;
	//if (OwnerActor == nullptr) return;
	//if (OtherActor == OwnerActor) return;
	//
	//AC_Unit* other = Cast<AC_Unit>(OtherActor);
	//if (other == nullptr) return;
	//if (other->GetGenericTeamId() == OwnerActor->GetGenericTeamId()) return;
	//
	//CLog::Print(L"ThrowingWeapon OnHit", 10.0f, FColor::Red);
}
