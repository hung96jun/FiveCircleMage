#include "Characters/Monster/C_Monster.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Weapons/Weapon/C_WeaponBase.h"

#include "Utilities/CLog.h"

AC_Monster::AC_Monster()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_Monster::BeginPlay()
{
	Super::BeginPlay();

	GenericTeamID = 2;

	ForceType = EUnitForceType::Monster;

	//// 몬스터 풀링 이전 테스트용 코드
	//{
	//	//AC_WeaponBase* weapon = GetWorld()->SpawnActor<AC_WeaponBase>();
	//	//AttachWeapon(weapon, L"RightWeaponSocket");
	//	//weapon->SetActive(true);
	//	//weapon->SetActorHiddenInGame(false);
	//	//weapon->SetDamage(10.0f);
	//
	//	UC_GameInstance* instance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	//	if (instance == nullptr) return;
	//
	//	AC_WeaponBase* weapon = Cast<AC_WeaponBase>(instance->GetWeaponManager()->ActiveWeapon(L"WeaponBase"));
	//	if (weapon == nullptr) return;
	//
	//	AttachWeapon(weapon, L"RightWeaponSocket");
	//	weapon->SetDamage(1.0f);
	//}
}

void AC_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector start, end, forward;
	//start = GetActorLocation();
	//forward = GetActorForwardVector();
	//end = start + (forward * 1000.0f);
	//end.Z = start.Z;
	//TArray<AActor*> ignores;
	//ignores.Add(this);
	//FHitResult hits;
	//bool bCheck = UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, 
	//	ETraceTypeQuery::TraceTypeQuery3, false, ignores, 
	//	EDrawDebugTrace::ForOneFrame, hits, true);

	//if (bCheck == true)
	//	
	// L"Trace Success", 0.01f, FColor::Red);
	//else
	//	CLog::Print(L"Trace Failed", 0.01f, FColor::Red);
}

void AC_Monster::SetAttackNum(const int Num)
{
	bAttacking = true;
	AttackNum = Num;
}

void AC_Monster::ResetAttackState()
{
	bAttacking = false;
	AttackNum = -1;
}

void AC_Monster::OnDeath()
{
	Super::OnDeath();

	if (Weapon != nullptr)
	{
		Weapon->SetActive(false);
	}
}

void AC_Monster::OnAttacking()
{
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear - Weapon is nullptr", 10.0f, FColor::Red);
		return;
	}
	else
		CLog::Print(L"Bear - Weapon is not nullptr", 10.0f, FColor::Blue);

	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AC_Monster::EndAttacking()
{
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear - Weapon is nullptr", 10.0f, FColor::Red);
		return;
	}
	else
		CLog::Print(L"Bear - Weapon is not nullptr", 10.0f, FColor::Blue);

	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AC_Monster::AttachWeapon(AC_WeaponBase* Actor, const FName BoneName, const FVector Extent, const FVector Offset)
{
	Weapon = Actor;
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear Object - Weapon is nullptr", 100.0f, FColor::Red);
		return;
	}

	Weapon->SetBoxExtent(Extent);
	Weapon->SetActorRelativeLocation(Offset);
}

void AC_Monster::AttachWeapon(const FName BoneName, const FVector Offset)
{
	if (Weapon == nullptr) return;

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear Object - Weapon is nullptr", 100.0f, FColor::Red);
		return;
	}

	Weapon->SetActorRelativeLocation(Offset);
}
