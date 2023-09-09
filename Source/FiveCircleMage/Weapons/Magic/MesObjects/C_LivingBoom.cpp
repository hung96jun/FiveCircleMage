// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Magic/MesObjects/C_LivingBoom.h"
#include "C_GameInstance.h"
#include "Managers/C_MagicManager.h"

AC_LivingBoom::AC_LivingBoom()
{
	PrimaryActorTick.bCanEverTick = true;

	OriginDelayTime = 10.0f;

	PatchCollision = CreateDefaultSubobject<UCapsuleComponent>("PatchCollision");
	PatchCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PatchCollision->SetupAttachment(RootComponent);
	PatchCollision->SetCapsuleHalfHeight(100.0f);
	PatchCollision->SetCapsuleRadius(100.0f);
}

void AC_LivingBoom::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_LivingBoom::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AC_LivingBoom::OnEndOverlap);
	PatchCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_LivingBoom::OnPatch);

	Collision->SetCollisionProfileName(L"Magic");
	PatchCollision->SetCollisionProfileName(L"Magic");

	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActiveCollision(false);
	ActivePatchCollision(false);

	Key = "11100";
}

void AC_LivingBoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_Unit* otherUnit;

	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	if (DelayTime < 0.0f) return;

	UnitsInArea.Add(otherUnit);
}

void AC_LivingBoom::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AC_Unit* otherUnit;

	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	UnitsInArea.Remove(otherUnit);
}

void AC_LivingBoom::OnPatch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Target != nullptr) return;

	AC_Unit* otherUnit;

	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	SetTarget(otherUnit);
	ActivePatchCollision(false);

	FVector targetOverHeadLocation = Target->GetActorLocation() + FVector(0, 0, Target->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
	SetActorLocation(targetOverHeadLocation);
}

void AC_LivingBoom::Tick(float DeltaTime)
{
	if (bActive == false) return;
	if (Duration < 0.0f) { bActive = false; return; }

	Super::Tick(DeltaTime);

	if (DelayTime < 0.5f && Collision->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		ActiveCollision(true);

	if (DelayTime > 0.0f)
	{
		DelayTime -= DeltaTime;

		if (DelayTime <= 0.0f)
			Boom();
	}
}

void AC_LivingBoom::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;

	UnitsInArea.Empty();
	Target = nullptr;
	MultipleCount = 0;
	DelayTime = OriginDelayTime;
	LifeTime = 0.0f;

	SetCastingRotation(Rotation);

	SetActorLocation(TargetPosition);

	ActivePatchCollision(true);

	PlayParticle(MAIN_PARTICLE);

	if (Duration < DelayTime)
		Duration = DelayTime + 1.0f;
}

void AC_LivingBoom::Boom()
{
	SetActorLocation(Target->GetActorLocation());
	for (AC_Unit* unit : UnitsInArea)
	{
		DamageComp->GiveDmg(unit, Damage, State);

		if (MultipleCount <= 0) continue;
		if (unit->GetName() == Target->GetName()) continue;

		// Spread living boom to other monsters as MultipleCount amount
		Cast<UC_GameInstance>(GetWorld()->GetGameInstance())->GetMagicManager()->OnFireMagic(OwnerActor, Key, FVector::ZeroVector, unit->GetActorLocation());
		MultipleCount--;
	}

	bActive = false;
	ActivePatchCollision(false);
	ActiveCollision(false);
}

void AC_LivingBoom::PlayParticle(int32 ParticleType)
{
	if (ParticleType == MAIN_PARTICLE)
	{
		MainParticle.Play(Collision);
		MainParticle.SetParticleScale(0.8f);
	}
	else if (ParticleType == END_PARTICLE && EndParticle.IsActive())
		EndParticle.Play(Collision);
	else if (ParticleType == SUB_PARTICLE && SubParticle.IsActive())
		SubParticle.Play(PatchCollision);
}

void AC_LivingBoom::SetTarget(AC_Unit* _Target)
{
	Target = _Target;
	FAttachmentTransformRules rule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}
