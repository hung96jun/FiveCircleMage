#include "Weapons/Magic/MesObjects/C_VampiricAreaSkill.h"

#include "Characters/C_Unit.h"

AC_VampiricAreaSkill::AC_VampiricAreaSkill()
{
}

void AC_VampiricAreaSkill::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_VampiricAreaSkill::OnBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AC_VampiricAreaSkill::OnEnd);
}

void AC_VampiricAreaSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_VampiricAreaSkill::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	Super::BeginCasting(CasterPosition, TargetPosition, Rotation);

	DamageInterval = DelayTime;

	DamageTimerDelegate.BindUFunction(this, "OnAction");
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegate, DamageInterval, true);
}

void AC_VampiricAreaSkill::OnActive()
{
	float totalHealAmount = 0.0f;

	for (AC_Unit* unit : OtherUnits)
	{
		if ((*unit->GetUnitStatus()->GetCurHP()) < 0.0f) continue;

		DamageComp->GiveDmg(unit, Damage);
		totalHealAmount += HealAmount;
	}

	DamageComp->GiveHeal(Owner, totalHealAmount);
}

void AC_VampiricAreaSkill::EndActive()
{
	Super::EndActive();

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
}

void AC_VampiricAreaSkill::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_Unit* otherUnit = nullptr;
	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	OtherUnits.Add(otherUnit);
}

void AC_VampiricAreaSkill::OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AC_Unit* otherUnit = nullptr;
	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	OtherUnits.Remove(otherUnit);
}
