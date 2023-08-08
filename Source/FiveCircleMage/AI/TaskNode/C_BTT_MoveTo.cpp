#include "AI/TaskNode/C_BTT_MoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/CLog.h"
#include "Utilities/Defines.h"

UC_BTT_MoveTo::UC_BTT_MoveTo()
{
	NodeName = L"BTT_MoveTo";

	bNotifyTick = true;
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

	//CLog::Print(L"Call MoveTo", 1.0f, FColor::Green);

	return EBTNodeResult::InProgress;
}

void UC_BTT_MoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	if (controller == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	if (blackboard == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	float acceptableDistance = 0.0f;
	if (AcceptableRadius >= 0.0f)
		acceptableDistance = AcceptableRadius;
	else
		acceptableDistance = blackboard->GetValueAsFloat(AcceptableKey.SelectedKeyName);

	float distance = blackboard->GetValueAsFloat(L"Distance");

	if (distance < acceptableDistance)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UC_BTT_MoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACharacter* owner = controller->GetCharacter();
	CheckNullResult(owner, EBTNodeResult::Failed);

	FVector start = owner->GetActorLocation();

	//UNavigationSystemV1::FindPathToLocationSynchronously()

	return EBTNodeResult::Type();
}
