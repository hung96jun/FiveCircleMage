#include "Characters/Monster/Spider/C_SpiderAnimInstance.h"
#include "KismetAnimationLibrary.h"

#include "Characters/Monster/C_Monster.h"

UC_SpiderAnimInstance::UC_SpiderAnimInstance()
{
}

void UC_SpiderAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<AC_Monster>(TryGetPawnOwner());
}

void UC_SpiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character == nullptr) return;

	Super::NativeUpdateAnimation(DeltaSeconds);

	Speed = Character->GetVelocity().Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
	bAttacking = Character->IsAttacking();
	bDeath = (*(Character->GetUnitStatus()->GetCurHP()) <= 0.0f) ? true : false;
}
