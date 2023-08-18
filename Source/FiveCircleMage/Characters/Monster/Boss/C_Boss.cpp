#include "Characters/Monster/Boss/C_Boss.h"

AC_Boss::AC_Boss()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Boss::GetDmg(const float Dmg, const EUnitState Type)
{
	Super::GetDmg(Dmg, Type);

	GroggyArmor -= Dmg;

	if (GroggyArmor <= 0.0f)
	{
		bOnGroggy = true;
		GroggyArmor = OriginGroggyArmor;
	}
}

void AC_Boss::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Boss::Tick(float DeltaTime)
{
	if (bIsActive == false) return;

	Super::Tick(DeltaTime);

	UpdateData(DeltaTime);
}

void AC_Boss::Spawn(FVector3d SpawnLocation)
{
	SetActorLocation(SpawnLocation);

	this->Init();
}

void AC_Boss::Init()
{
	bIsActive = true;

	bOnGroggy = false;

	bEnableSpawnedShout = false;
	bSpawnedShouting = false;

	bEnableRangedAttack = false;
	bRangedAttacking = false;

	bEnableMeleeAttack = false;
	bMeleeAttacking = false;

	bAttacking = false;

	CurSpawnedMinions = 0;

	UnitStatus.InitStatus();
}

void AC_Boss::UpdateData(float DeltaTime)
{
	DistanceToTarget = (TargetLocation - GetActorLocation()).Length();

}

void AC_Boss::MeleeAttack()
{
	bAttacking = true;

	//active collision on hands
}

void AC_Boss::RangedAttack()
{
	bAttacking = true;

	//fire missile
}

void AC_Boss::SpawnedShout()
{
	bAttacking = true;

	//spawn minions
}
