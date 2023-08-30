#include "AI/TaskNode/C_BTT_MoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Characters/C_Unit.h"
#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/CLog.h"
#include "Utilities/Defines.h"

UC_BTT_MoveTo::UC_BTT_MoveTo()
{
	NodeName = L"BTT_MoveTo";

	bNotifyTick = true;
	bNotifyTaskFinished = true;

	// 필터를 Object와 Vector로 설정
	Target.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UC_BTT_MoveTo, Target), AActor::StaticClass());
	Target.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UC_BTT_MoveTo, Target));
}

EBTNodeResult::Type UC_BTT_MoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACharacter* owner = controller->GetCharacter();
	CheckNullResult(owner, EBTNodeResult::Failed);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNullResult(blackboard, EBTNodeResult::Failed);

	//UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(owner->GetWorld());
	//CheckNullResult(navSystem, EBTNodeResult::Failed);

	FAIMoveRequest moveInfo;

	// 타겟 키가 Actor일때
	if (bTargetActor == true && bTargetVector == false)
	{
		TargetActor = Cast<AActor>(blackboard->GetValueAsObject(Target.SelectedKeyName));
		//TargetLocation = target->GetActorLocation();
		if (TargetActor == nullptr)
			return EBTNodeResult::Failed;
		moveInfo.SetGoalActor(TargetActor);
	}

	// 타겟 키가 Vector일때
	else if (bTargetVector == true && bTargetActor == false)
	{
		//TargetLocation = blackboard->GetValueAsVector(Target.SelectedKeyName);
		moveInfo.SetGoalLocation(blackboard->GetValueAsVector(Target.SelectedKeyName));
	}

	// 잘못된 설정값
	else
	{
		CLog::Print(L"Target : Failed", 10.0f, FColor::Red);
		return EBTNodeResult::Failed;
	}
	
	// 허용 범위가 설정되어있을때
	if (AcceptableRadius > 0.0f)
	{
		AcceptableDistance = AcceptableRadius;
		AcceptableDistance -= FMath::FRandRange(0.0f, AcceptableRandomRadius);
	}

	// 허용 범위가 키로 설정되었을때
	else
	{
		AcceptableDistance = blackboard->GetValueAsFloat(AcceptableKey.SelectedKeyName);
		AcceptableDistance -= FMath::FRandRange(0.0f, AcceptableRandomRadius);
	}

	//moveInfo.SetAcceptanceRadius(AcceptableDistance);

	FNavPathSharedPtr navPath;
	controller->MoveTo(moveInfo, &navPath);

	CurTimer = 0.0f;

	return EBTNodeResult::InProgress;
}

void UC_BTT_MoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	if (controller == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	AC_Unit* owner = Cast<AC_Unit>(controller->GetCharacter());
	if (owner == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	if (blackboard == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	//if ((*owner->GetUnitStatus()->GetCurHP()) <= 0.0f)
	//{
	//	CLog::Print(L"MoveTo TaskNode - TickTask function(Abort condition success)", 10.0f, FColor::Red);
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
	//}

	float distance = blackboard->GetValueAsFloat(L"Distance");
	
	// 현재 타겟과의 거리가 허용범위 보다 작을 경우
	if (distance < AcceptableDistance)
	{
		// 트레이스가 설정되었을때
		if (bTraceCheck == true)
		{
			FVector start, end;
			start = owner->GetActorLocation();
			end = TargetActor->GetActorLocation();

			TArray<AActor*> ignores;
			ignores.Add(owner);
			ignores.Add(TargetActor);

			FHitResult hit;
			bool bHit = UKismetSystemLibrary::LineTraceSingle(owner->GetWorld(),
				start, end, ETraceTypeQuery::TraceTypeQuery1, false,
				ignores, EDrawDebugTrace::ForOneFrame, hit, true);

			if (bHit == false)
			{
				CLog::Print(L"MoveTo - TracekCheck Finish", 10.0f, FColor::Red);
				owner->GetCharacterMovement()->StopMovementImmediately();
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}

		else
		{
			CLog::Print(L"MoveTo - not TracekCheck Finish", 10.0f, FColor::Red);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	else if (CurTimer >= ResetTime)
	{
		CLog::Print(L"MoveTo - TimeOver Finish", 10.0f, FColor::Red);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	CurTimer += DeltaSeconds;
}

EBTNodeResult::Type UC_BTT_MoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACharacter* owner = controller->GetCharacter();
	CheckNullResult(owner, EBTNodeResult::Failed);

	CLog::Print(L"Call MoveTo TaskNode - AbortTask function", 10.0f, FColor::Red);
	owner->GetCharacterMovement()->StopMovementImmediately();

	return EBTNodeResult::Failed;
}
