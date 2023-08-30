// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Monster/Boss/C_BossAnimInstance.h"

#include "Characters/Monster/Boss/C_Boss.h"

UC_BossAnimInstance::UC_BossAnimInstance()
{
}

void UC_BossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<AC_Boss>(TryGetPawnOwner());
}

void UC_BossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character == nullptr) return;

	Super::NativeUpdateAnimation(DeltaSeconds);

	bAttacking = Character->GetOnAttacking();
	bOnGroggy = Character->GetGroggy();
	bIsDead = Character->GetIsDead();
	bMeleeAttacking = Character->GetMeleeAttack();
	bRangedAttacking = Character->GetRangedAttack();
	bSpawnedShouting = Character->GetSpawnedShouting();
	Speed = Character->GetVelocity().Size();
}
