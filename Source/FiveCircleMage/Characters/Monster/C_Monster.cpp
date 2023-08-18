#include "Characters/Monster/C_Monster.h"
#include "BehaviorTree/BehaviorTree.h"

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
