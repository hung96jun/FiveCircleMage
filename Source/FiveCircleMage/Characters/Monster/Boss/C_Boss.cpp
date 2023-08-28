#include "Characters/Monster/Boss/C_Boss.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AC_Boss::AC_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AC_BossAIController::StaticClass();

	FString path = L"Engine.SkeletalMesh'/Game/Assets/InfinityBladeAdversaries/Enemy/Enemy_Frost_Giant/SK_Enemy_FrostGiant_Captain.SK_Enemy_FrostGiant_Captain'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(*path);

	if (mesh.Succeeded())
		GetMesh()->SetSkeletalMesh(mesh.Object);
}

void AC_Boss::GetDmg(const float Dmg, const EUnitState Type)
{
	Super::GetDmg(Dmg, Type);

	GroggyArmor -= Dmg;

	if (GroggyArmor <= 0.0f)
	{
		bOnGroggy = true;
	}

	if (bOnSecondPhase == false && CurHPRate() < 0.5f)
	{
		BeginSecondPhase();
	}
	else if(bIsDead == false && UnitStatus.IsDeath())
	{
		Dead();
	}
}

void AC_Boss::SetBehaviorTree(UBehaviorTree* BT, UBlackboardComponent* BB)
{
	BTAsset = BT;
	BBAsset = BB;

	SetValueAtBB();
}

void AC_Boss::BeginPlay()
{
	Super::BeginPlay();

	// 초기설정값 지정

	UnitStatus = FUnitStatus(2000.0f, 50.0f);
	Init();
}

void AC_Boss::Tick(float DeltaTime)
{
	if (bIsActive == false) return;

	Super::Tick(DeltaTime);

	UpdateData(DeltaTime);
	SetValueAtBB();
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
}

void AC_Boss::SetValueAtBB()
{
	// OnAttacking
	BBAsset->SetValueAsBool(L"bOnAttacking", bAttacking);

	// Melee
	BBAsset->SetValueAsBool(L"bOnMeleeAttacking", bMeleeAttacking);
	BBAsset->SetValueAsBool(L"bEnableMeleeAttacking", bEnableMeleeAttack);

	// Ranged
	BBAsset->SetValueAsBool(L"bOnRangedAttacking", bRangedAttacking);
	BBAsset->SetValueAsBool(L"bEnableRangedAttacking", bEnableRangedAttack);

	// Spawned Shout
	BBAsset->SetValueAsBool(L"bOnShouting", bSpawnedShouting);
	BBAsset->SetValueAsBool(L"bEnableShouting", bEnableSpawnedShout);

	// Dead
	BBAsset->SetValueAsBool(L"bIsDead", bIsDead);

	// OnGroggy
	BBAsset->SetValueAsBool(L"bOnGroggy", bOnGroggy);

	// HP Rate
	BBAsset->SetValueAsFloat(L"HPRate", CurHPRate());

	// Second Phase
	BBAsset->SetValueAsBool(L"bOnSecondPhase", bOnSecondPhase);

	// Distance
	if (Target != nullptr)
	{
		DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Length();
		BBAsset->SetValueAsFloat(L"Distance", DistanceToTarget);
	}
}

void AC_Boss::BeginSecondPhase()
{
	bOnSecondPhase = true;
	bOnGroggy = false;
	GroggyArmor = 0.0f;

	//아우라 비저블
}

void AC_Boss::Dead()
{
	bIsDead = true;
	bIsActive = false;
}

void AC_Boss::OnMeleeAttack()
{
	bAttacking = true;
	bEnableMeleeAttack = false;
	bMeleeAttacking = true;

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

	//spawn minions
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