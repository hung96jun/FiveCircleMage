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
		ParticleInfos.SetNum(2);

		for (int32 idx = 0; idx < ParticleInfos.Num();idx++)
		{
			if(idx == 0)
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

	// �ʱ⼳���� ����

	UnitStatus = FUnitStatus(2000.0f, 250.0f);

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
	weapon->SetOwnerActor(this);

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

	UnitStatus.InitStatus();
	GroggyArmor = OriginGroggyArmor;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//GetMesh()->bHiddenInGame = false;
	SetActorHiddenInGame(false);
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

	if (!bEnableRangedAttack)
	{
		RangedAttackFrame += DeltaTime;
		if (RangedAttackFrame >= RangedAttackSpeed)
		{
			RangedAttackFrame = 0.0f;
			bEnableRangedAttack = true;
		}
	}

	if (!bEnableMeleeAttack)
	{
		MeleeAttackFrame += DeltaTime;
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

//void AC_Boss::SetValueAtBB()
//{
//	// OnAttacking
//	BBAsset->SetValueAsBool(L"bOnAttacking", bAttacking);
//
//	// Melee
//	BBAsset->SetValueAsBool(L"bOnMeleeAttacking", bMeleeAttacking);
//	BBAsset->SetValueAsBool(L"bEnableMeleeAttacking", bEnableMeleeAttack);
//
//	// Ranged
//	BBAsset->SetValueAsBool(L"bOnRangedAttacking", bRangedAttacking);
//	BBAsset->SetValueAsBool(L"bEnableRangedAttacking", bEnableRangedAttack);
//
//	// Spawned Shout
//	BBAsset->SetValueAsBool(L"bOnShouting", bSpawnedShouting);
//	BBAsset->SetValueAsBool(L"bEnableShouting", bEnableSpawnedShout);
//
//	// Dead
//	BBAsset->SetValueAsBool(L"bIsDead", bIsDead);
//
//	// OnGroggy
//	BBAsset->SetValueAsBool(L"bOnGroggy", bOnGroggy);
//
//	// HP Rate
//	BBAsset->SetValueAsFloat(L"HPRate", CurHPRate());
//
//	// Second Phase
//	BBAsset->SetValueAsBool(L"bOnSecondPhase", bOnSecondPhase);
//
//	// Distance
//	if (Target != nullptr)
//	{
//		DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Length();
//		BBAsset->SetValueAsFloat(L"Distance", DistanceToTarget);
//	}
//}

void AC_Boss::BeginSecondPhase()
{
	bOnSecondPhase = true;
	bOnGroggy = false;
	GroggyArmor = 0.0f;

	//�ƿ�� ������
	ParticleInfos[1].SetLocation(FVector(0, 0, -25.f));

	for (FParticleInfo& info : ParticleInfos)
		info.Play(GetCapsuleComponent());
}

void AC_Boss::Dead()
{
	bIsDead = true;
	bIsActive = false;

	BossUI->Hide();
	BossUI = nullptr;
}

void AC_Boss::OnMeleeAttack()
{
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
	//// ��ġ����?
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