#include "Weapons/Magic/C_MagicMissile.h"

AC_MagicMissile::AC_MagicMissile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_MagicMissile::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_MagicMissile::OnBeginOverlap);
}

void AC_MagicMissile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CLog::Print(L"BeginOverlap - " + OtherActor->GetActorLabel(), 10.0f, FColor::Red);
	CLog::Print(L"OtherActor == nullptr", 10.0f, FColor::Red);
	if (OtherActor == nullptr) return;
	CLog::Print(L"OtherActor == this", 10.0f, FColor::Red);
	if (OtherActor == this) return;
	CLog::Print(L"OtherActor == OwnerActor", 10.0f, FColor::Red);
	if (OtherActor == OwnerActor) return;
	CLog::Print(L"Clear", 10.0f, FColor::Red);
	CLog::Print(L"BeginOverlap - " + OwnerActor->GetActorLabel(), 10.0f, FColor::Red);

	DamageComp->GiveDmg(OtherActor, Damage, State);
	bActive = false;

	ActiveCollision(false);

	if (EndParticle.IsActive())
		PlayParticle(END_PARTICLE);
}

void AC_MagicMissile::Tick(float DeltaTime)
{
	if (bActive == false) return;
	if (Duration < 0.0f)
	{
		bActive = false;
		return;
	}

	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AC_MagicMissile::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;

	SetCastingRotation(Rotation);

	SetActorLocation(CasterPosition);

	MoveDirection = (TargetPosition - CasterPosition).GetSafeNormal();

	PlayParticle(MAIN_PARTICLE);

	ActiveCollision(true);
}

void AC_MagicMissile::Move(float DeltaTime)
{
	FVector Location = GetActorLocation() + MoveSpeed * MoveDirection * DeltaTime;

	SetActorLocation(Location); 
}