#include "Characters/Monster/Boss/C_Boss.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "C_GameInstance.h"
#include "Managers/C_WeaponManager.h"
#include "Managers/C_MonsterManager.h"
#include "Characters/Monster/C_Monster.h"
#include "Characters/Monster/Boss/C_BossAnimInstance.h"

#include "UI/C_BossUI.h"

AC_Boss::AC_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//AIControllerClass = AC_BossAIController::StaticClass();

	FString path = L"Engine.SkeletalMesh'/Game/Assets/InfinityBladeAdversaries/Enemy/Enemy_Frost_Giant/SK_Enemy_FrostGiant_Captain.SK_Enemy_FrostGiant_Captain'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(*path);

	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -160.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(180.0f);
	GetCapsuleComponent()->SetCapsuleRadius(100.0f);

	{
		path = L"/Script/Engine.AnimBlueprint'/Game/Blueprint/Characters/Enemy/Boss/BpC_BossAnimInstance.BpC_BossAnimInstance_C'";
		ConstructorHelpers::FClassFinder<UAnimInstance> anim(*path);

		if(anim.Succeeded())
			GetMesh()->SetAnimInstanceClass(anim.Class);
	}

	{
		path = L"/Script/Engine.AnimBlueprint'/Game/Blueprint/Characters/Enemy/Boss/BpC_BossAnimInstance.BpC_BossAnimInstance_C'";
		ConstructorHelpers::FClassFinder<UAnimInstance> anim(*path);

		if (anim.Succeeded())
			GetMesh()->SetAnimInstanceClass(anim.Class);
	}

	{
		ParticleInfos.SetNum(2);

		for (int32 idx = 0; idx < ParticleInfos.Num(); idx++)
		{
			if (idx == 0)
				path = L"/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/Sci-Fi_Starter_VFX_Pack_Niagara/Niagara/Explosion/NS_BossCharge.NS_BossCharge'";
			else if (idx == 1)
				path = L"/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/Sci-Fi_Starter_VFX_Pack_Niagara/Niagara/Explosion/NS_BossWind.NS_BossWind'";

			ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);

			if (niagara.Succeeded())
				ParticleInfos[idx].SetParticle(niagara.Object, FVector::ZeroVector, FRotator::ZeroRotator);
		}
	}
}

void AC_Boss::BeginPlay()
{
	Super::BeginPlay();

	// 초기설정값 지정

	UnitStatus = FUnitStatus(1000.0f, 250.0f);

	// Capsule collision setting
	GetCapsuleComponent()->SetCapsuleRadius(80.0f);

	Init();

	// Set rightHand collision for melee attack
	UC_GameInstance* instance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	if (instance == nullptr) return;

	AC_WeaponBase* weapon = Cast<AC_WeaponBase>(instance->GetWeaponManager()->ActiveWeapon(L"BossHand"));
	if (weapon == nullptr) return;

	Weapon = weapon;
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, L"RightWeaponSocket");
	if (Weapon == nullptr)
	{
		CLog::Print(L"Boss Object - Weapon is nullptr", 100.0f, FColor::Red);
		return;
	}

	Weapon->SetBoxExtent(FVector(60.0f, 50.0f, 50.0f));
	Weapon->SetActorRelativeLocation(FVector(45.0f, 0, 0));
	Weapon->SetOwnerActor(this);

	ForceType = EUnitForceType::Monster;
}

void AC_Boss::Tick(float DeltaTime)
{
	if (bIsActive == false) return;

	Super::Tick(DeltaTime);

	UpdateData(DeltaTime);
	//SetValueAtBB();
}

void AC_Boss::GetDmg(const float Dmg, const EUnitState Type)
{
	Super::GetDmg(Dmg, Type);

	GroggyArmor -= Dmg;

	if (BossUI != nullptr)
		BossUI->Update();

	if (GroggyArmor <= 0.0f)
	{
		bOnGroggy = true;
	}

	if (bOnSecondPhase == false && CurHPRate() < 0.5f)
	{
		BeginSecondPhase();
	}
	else if (bIsDead == false && UnitStatus.IsDeath())
	{
		Dead();
	}
}

void AC_Boss::SetBehaviorTree(UBehaviorTree* BT, UBlackboardComponent* BB)
{
	BTAsset = BT;
	BBAsset = BB;

	//SetValueAtBB();
}

void AC_Boss::Spawn(FVector3d SpawnLocation)
{
	SetActorLocation(SpawnLocation);

	this->Init();
	UnitStatus.InitStatus();
}

void AC_Boss::Init()
{
	bIsActive = true;
	bIsDead = false;

	bOnGroggy = false;

	bEnableSpawnedShout = true;
	bSpawnedShouting = false;

	bEnableRangedAttack = true;
	bRangedAttacking = false;

	bEnableMeleeAttack = true;
	bMeleeAttacking = false;

	bAttacking = false;

	CurSpawnedMinions = 0;

	GroggyArmor = OriginGroggyArmor;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//GetMesh()->bHiddenInGame = false;
	SetActorHiddenInGame(false);

	// Test
	//bOnSecondPhase = true;
	//BeginSecondPhase();
}

void AC_Boss::NaturalHeal(float DeltaTime)
{
	if (bAttacking == true) return;

	bool bIsMaxHP = UnitStatus.GetHPRate() >= 1.0f;
	bool bIsMaxArmor = GroggyArmor >= OriginGroggyArmor;

	if (bIsMaxHP == false)
	{
		float healAmount = bOnSecondPhase ? DeltaTime : DeltaTime * 2.0f;
		*UnitStatus.GetCurHP() += healAmount;
	}

	if (bIsMaxArmor == false)
	{
		float armorRecoverAmount = bOnSecondPhase ? DeltaTime * 0.2f : DeltaTime * 0.4f * 2.0f;
		if (bOnGroggy == true)
			armorRecoverAmount *= 5.0f;
		GroggyArmor += armorRecoverAmount;
	}
}

void AC_Boss::UpdateData(float DeltaTime)
{
	DistanceToTarget = (TargetLocation - GetActorLocation()).Length();

	float timeMagnification = 1.0f;
	if (bOnSecondPhase == true)
		timeMagnification = 2.0f;

	if (!bEnableRangedAttack)
	{
		RangedAttackFrame += DeltaTime * timeMagnification;
		if (RangedAttackFrame >= RangedAttackSpeed)
		{
			RangedAttackFrame = 0.0f;
			bEnableRangedAttack = true;
		}
	}

	if (!bEnableMeleeAttack)
	{
		MeleeAttackFrame += DeltaTime * timeMagnification;
		if (MeleeAttackFrame >= MeleeAttackSpeed)
		{
			MeleeAttackFrame = 0.0f;
			bEnableMeleeAttack = true;
		}
	}

	if (!bEnableSpawnedShout)
	{
		SpawnedShoutFrame += DeltaTime;
		if (SpawnedShoutFrame >= SpawnedShoutSpeed)
		{
			SpawnedShoutFrame = 0.0f;
			bEnableSpawnedShout = true;
		}
	}

	NaturalHeal(DeltaTime);
}

void AC_Boss::BeginSecondPhase()
{
	bOnSecondPhase = true;
	bOnGroggy = false;
	GroggyArmor = OriginGroggyArmor;

	float curHP = (*UnitStatus.GetCurHP());
	UnitStatus.DecreaseMoveSpeed(-0.4);

	//아우라 비저블
	ParticleInfos[1].SetLocation(FVector(0, 0, -25.f));

	for (FParticleInfo& info : ParticleInfos)
		info.Play(GetCapsuleComponent());

	UC_GameInstance* instance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	if (instance == nullptr) return;

	instance->CinemaPlay(L"BossSecondPhase");
}

void AC_Boss::Dead()
{
	bIsDead = true;
	bIsActive = false;

	BossUI->Hide();
	BossUI = nullptr;
}

void AC_Boss::WeaponChangeBone(FName BoneName, FVector OffsetLocation, FRotator OffsetRotation)
{
	if (Weapon == nullptr) return;

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	Weapon->SetActorRelativeLocation(OffsetLocation);
	Weapon->SetActorRelativeRotation(OffsetRotation);
}

void AC_Boss::OnMeleeAttack()
{
	if (bOnSecondPhase == true)
	{
		MeleeAttackNum = UKismetMathLibrary::RandomInteger(MaxMeleeAttackNum) + 1;
		CLog::Print(L"SecondPhase Attack - " + FString::FromInt(MeleeAttackNum), 10.0f, FColor::Green);
	}

	bAttacking = true;
	bEnableMeleeAttack = false;
	bMeleeAttacking = true;

	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//active collision on hands
}

void AC_Boss::OnRangedAttack()
{
	bAttacking = true;
	bEnableRangedAttack = false;
	bRangedAttacking = true;
	//fire missile
}

void AC_Boss::OnSpawnedShout()
{
	bAttacking = true;
	bEnableSpawnedShout = false;
	bSpawnedShouting = true;

	//////////////////////////////////////////////////////////////////////////////////
	//spawn minions
	//FString monsterName = L"";
	//
	//UC_GameInstance* instance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	//if (instance == nullptr) return;
	//if (instance->GetMonsterManager() == nullptr) return;
	//if (instance->GetMonsterManager()->FindMonster(monsterName) == false) return;
	//
	//TArray<FVector> locations;
	//
	//// 위치지정?
	//for (int iter = 0; iter < SpawnAmount; iter--)
	//{
	//	FVector local;
	//	locations.Push(local);
	//}
	//instance->GetMonsterManager()->SpawnningMonster(monsterName, locations);
	//////////////////////////////////////////////////////////////////////////////////
}

void AC_Boss::OnGroggy()
{
	if (GroggyArmor < OriginGroggyArmor)
	{
		GroggyArmor += GroggyArmorRegeneratedPower * GetWorld()->GetDeltaSeconds();
	}
	else
	{
		GroggyArmor = OriginGroggyArmor;
		bOnGroggy = false;
	}
}