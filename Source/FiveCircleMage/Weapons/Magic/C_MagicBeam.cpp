#include "Weapons/Magic/C_MagicBeam.h"

AC_MagicBeam::AC_MagicBeam()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetCollisionProfileName(L"Magic");
	Capsule->SetCapsuleHalfHeight(1.0f);
	Capsule->SetCapsuleRadius(1.0f);
}

void AC_MagicBeam::BeginPlay()
{
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_MagicBeam::OnBeginOverlap);

	EndTimerDelegate.BindUFunction(this, L"EndBeam");
}

void AC_MagicBeam::Tick(float DeltaTime)
{
	//if (bActive == false)
	//{
	//	CLog::Print(L"Beam Active is false", 10.0f, FColor::Red);
	//	return;
	//}
	//if (Duration <= 0.0f)
	//{
	//	bActive = false;
	//	ActiveCollision(false);
	//	MainParticle.Stop();
	//	EndParticle.Stop();

	//	CLog::Print(L"Beam Duration Over", 10.0f, FColor::Red);

	//	return;
	//}

	Super::Tick(DeltaTime);

	CLog::Print(L"Beam Duration : " + FString::SanitizeFloat(Duration), 0.01f, FColor::Red);
}

void AC_MagicBeam::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;

	SetCastingRotation(Rotation);

	SetActorLocation(CasterPosition);

	PlayParticle(MAIN_PARTICLE);
	PlayParticle(END_PARTICLE);

	ActiveCollision(true);
	SetBeamPosition(CasterPosition, Rotation);

	GetWorld()->GetTimerManager().SetTimer(EndTimerHandle, EndTimerDelegate, OriginDuration, false);
}

void AC_MagicBeam::PlayParticle(int32 ParticleType)
{
	if (ParticleType == MAIN_PARTICLE)
		MainParticle.Play(Capsule);
	else if (ParticleType == END_PARTICLE && EndParticle.IsActive())
		EndParticle.Play(Capsule);
	else if (ParticleType == SUB_PARTICLE && SubParticle.IsActive())
		SubParticle.Play(Capsule);
}

void AC_MagicBeam::SetBeamPosition(FVector CasterLocation, FRotator CasterRotation)
{
	FVector farFromCaster = GetActorForwardVector() * 100.0f;

	FVector location = GetActorLocation() + farFromCaster + GetActorForwardVector() * Collision->GetScaledCapsuleHalfHeight();
	FRotator rotation = GetActorRotation() + FRotator(-90, 0, 0);

	Collision->SetRelativeLocation(location);
	Collision->SetRelativeRotation(rotation);

	Capsule->SetRelativeLocation(CasterLocation + farFromCaster);
	Capsule->SetRelativeRotation(CasterRotation);
}

void AC_MagicBeam::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsOtherActor(OtherActor) == false) return;

	DamageComp->GiveDmg(OtherActor, Damage, State);
}

void AC_MagicBeam::EndBeam()
{
	bActive = false;
	ActiveCollision(false);
	MainParticle.Stop();
	EndParticle.Stop();

	GetWorld()->GetTimerManager().ClearTimer(EndTimerHandle);
}
