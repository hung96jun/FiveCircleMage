// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Monster/Boss/C_BossAnimInstance.h"

#include "Characters/Monster/Boss/C_Boss.h"
#include "Utilities/CLog.h"

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
	bMeleeAttacking = Character->GetMeleeAttack();
	bRangedAttacking = Character->GetRangedAttack();
	bSpawnedShouting = Character->GetSpawnedShouting();
	Speed = Character->GetVelocity().Size();
	bFullArmor = Character->IsArmorFull();

	bSecondPhase = Character->GetSecondPhase();
	AttackNum = Character->GetMeleeAttackNum();
	bDeath = Character->GetIsDead();

	CLog::Print(L"BossAttackNum : " + FString::FromInt(AttackNum), 0.01f, FColor::Magenta);
	if (bAttacking == true)
		CLog::Print(L"BossAttack : true", 0.01f, FColor::Magenta);
	else
		CLog::Print(L"BossAttack : false", 0.01f, FColor::Magenta);
	if (bMeleeAttacking == true)
		CLog::Print(L"BossMeleeAttack : true", 0.01f, FColor::Magenta);
	else
		CLog::Print(L"BossMeleeAttack : false", 0.01f, FColor::Magenta);
	if (bDeath == true)
		CLog::Print(L"BossDeath : true", 0.01f, FColor::Magenta);
	else
		CLog::Print(L"BossDeath : false", 0.01f, FColor::Magenta);
}
