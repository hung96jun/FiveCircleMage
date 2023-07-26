#include "Weapons/Magic/MesObjects/C_BlackHoleSkill.h"

AC_BlackHoleSkill::AC_BlackHoleSkill()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AC_BlackHoleSkill::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_BlackHoleSkill::OnBegin);
}

void AC_BlackHoleSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BlackHoleSkill::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	Super::BeginCasting(CasterPosition, TargetPosition, Rotation);

	DamageTimerDelegate.BindUFunction(this, "OnActive");
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegate, DamageInterval, true);

	ChangeTimerDelegate.BindUFunction(this, "ChangeState");
	GetWorld()->GetTimerManager().SetTimer(ChangeTimerHandle, ChangeTimerDelegate, DelayTime, false);
}

void AC_BlackHoleSkill::OnInhalation()
{
	BlackHoleState = EBlackHoleState::Inhalation;

	Damage = InhalationDamage;
}

void AC_BlackHoleSkill::OnExplosion()
{
	BlackHoleState = EBlackHoleState::Explosion;

	Damage = ExplosionDamage;
}

void AC_BlackHoleSkill::EndActive()
{
	Super::EndActive();

	BlackHoleState = EBlackHoleState::None;
	OtherUnits.Empty();
}

void AC_BlackHoleSkill::OnActive()
{
	switch (BlackHoleState)
	{
	case EBlackHoleState::Inhalation:
	{
		FVector location = GetActorLocation();
		for (AC_Unit* unit : OtherUnits)
		{
			if ((*unit->GetUnitStatus()->GetCurHP()) < 0.0f) continue;

			FVector otherLocation = unit->GetActorLocation();
			FVector direction = location - otherLocation;
			direction.Z = 0.0f;
			float distance = direction.Size();
			direction.Normalize();
			direction *= distance;
			direction.Z = InhalationHeight;

			unit->LaunchCharacter(direction, true, true);
			DamageComp->GiveDmg(unit, Damage);
		}
	}
		break;
	case EBlackHoleState::Explosion:
	{
		for (AC_Unit* unit : OtherUnits)
		{
			if ((*unit->GetUnitStatus()->GetCurHP()) < 0.0f) return;

			DamageComp->GiveDmg(unit, Damage);
		}
	}
		break;
	}
}

void AC_BlackHoleSkill::ChangeState()
{
	OnExplosion();
	PlayParticle(END_PARTICLE);
}

void AC_BlackHoleSkill::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_Unit* otherUnit = nullptr;
	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	OtherUnits.Add(otherUnit);
}
