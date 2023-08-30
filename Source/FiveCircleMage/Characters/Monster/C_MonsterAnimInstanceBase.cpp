#include "Characters/Monster/C_MonsterAnimInstanceBase.h"
#include "KismetAnimationLibrary.h"

#include "Characters/Monster/C_Monster.h"

UC_MonsterAnimInstanceBase::UC_MonsterAnimInstanceBase()
{
}

void UC_MonsterAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<AC_Monster>(TryGetPawnOwner());
}

void UC_MonsterAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character == nullptr) return;

	Super::NativeUpdateAnimation(DeltaSeconds);

	Speed = Character->GetVelocity().Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
	bAttacking = Character->IsAttacking();
	bDeath = (*(Character->GetUnitStatus()->GetCurHP()) <= 0.0f) ? true : false;
	AttackNum = Character->GetAttackNum();
}
