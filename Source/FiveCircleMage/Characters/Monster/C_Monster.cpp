#include "Characters/Monster/C_Monster.h"
#include "BehaviorTree/BehaviorTree.h"


AC_Monster::AC_Monster()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_Monster::BeginPlay()
{
	Super::BeginPlay();

	GenericTeamID = 2;
}

void AC_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Monster::SetAttackNum(const int Num)
{
	bAttacking = true;
	AttackNum = Num;
}
