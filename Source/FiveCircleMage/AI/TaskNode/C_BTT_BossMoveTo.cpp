#include "AI/TaskNode/C_BTT_BossMoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Characters/Monster/C_Boss.h"

#include "Utilities/Defines.h"

UC_BTT_BossMoveTo::UC_BTT_BossMoveTo()
{
}

EBTNodeResult::Type UC_BTT_BossMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACharacter* owner = controller->GetCharacter();
	CheckNullResult(owner, EBTNodeResult::Failed);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNullResult(blackboard, EBTNodeResult::Failed);

	FVector targetLocation = FVector::ZeroVector;

	if (Target.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		AActor* target = Cast<AActor>(blackboard->GetValueAsObject(Target.SelectedKeyName));
		targetLocation = target->GetActorLocation();
	}
	else if (Target.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		targetLocation = blackboard->GetValueAsVector(Target.SelectedKeyName);
	}

	FAIMoveRequest moveInfo;
	moveInfo.SetGoalLocation(targetLocation);
	FNavPathSharedPtr navPath;
	controller->MoveTo(moveInfo, &navPath);

	return EBTNodeResult::InProgress;
}

void UC_BTT_BossMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UC_BTT_BossMoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}
