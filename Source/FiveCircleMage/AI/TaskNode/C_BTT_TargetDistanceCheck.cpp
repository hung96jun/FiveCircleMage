#include "AI/TaskNode/C_BTT_TargetDistanceCheck.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"
#include "Utilities/Defines.h"

#include "Utilities/CLog.h"

UC_BTT_TargetDistanceCheck::UC_BTT_TargetDistanceCheck()
{
	NodeName = L"BTT_TargetDistanceCheck";
}

EBTNodeResult::Type UC_BTT_TargetDistanceCheck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	float distance = controller->GetBlackboardComponent()->GetValueAsFloat("Distance");
	float compairDistance = controller->GetBlackboardComponent()->GetValueAsFloat("AttackRange");

	if (distance < compairDistance)
		EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UC_BTT_TargetDistanceCheck::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		CLog::Print(L"OwnerComp.GetAIOwner() == nullptr", 0.01f, FColor::Red);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		CLog::Print(L"controller == nullptr", 0.01f, FColor::Red);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	float distance = controller->GetBlackboardComponent()->GetValueAsFloat("Distance");
	float compairDistance = controller->GetBlackboardComponent()->GetValueAsFloat("AttackRange");

	if (distance <= compairDistance)
	{
		CLog::Print(L"distance < compairDistance", 0.01f, FColor::Red);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
