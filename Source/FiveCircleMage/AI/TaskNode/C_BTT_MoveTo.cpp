#include "AI/TaskNode/C_BTT_MoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/CLog.h"
#include "Utilities/Defines.h"

UC_BTT_MoveTo::UC_BTT_MoveTo()
{
	NodeName = L"BTT_MoveTo";

	bNotifyTick = true;

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

	if (bTargetActor == true && bTargetVector == false)
	{
		TargetActor = Cast<AActor>(blackboard->GetValueAsObject(Target.SelectedKeyName));
		//TargetLocation = target->GetActorLocation();
		if (TargetActor == nullptr)
			return EBTNodeResult::Failed;
		moveInfo.SetGoalActor(TargetActor);
	}

	else if (bTargetVector == true && bTargetActor == false)
	{
		//TargetLocation = blackboard->GetValueAsVector(Target.SelectedKeyName);
		moveInfo.SetGoalLocation(blackboard->GetValueAsVector(Target.SelectedKeyName));
	}

	else
	{
		CLog::Print(L"Target : Failed", 10.0f, FColor::Red);
		return EBTNodeResult::Failed;
	}
	
	if (AcceptableRadius > 0.0f)
	{
		AcceptableDistance = AcceptableRadius;
		AcceptableDistance -= FMath::FRandRange(0.0f, AcceptableRandomRadius);
	}
	else
	{
		AcceptableDistance = blackboard->GetValueAsFloat(AcceptableKey.SelectedKeyName);
		AcceptableDistance -= FMath::FRandRange(0.0f, AcceptableRandomRadius);
	}

	FNavPathSharedPtr navPath;
	controller->MoveTo(moveInfo, &navPath);

	CurTimer = 0.0f;

	CLog::Print(L"Call MoveTo", 1.0f, FColor::Green);

	return EBTNodeResult::InProgress;
}

void UC_BTT_MoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	if (controller == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	ACharacter* owner = controller->GetCharacter();
	if (owner == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	if (blackboard == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	FString debug = L"";

	float distance = blackboard->GetValueAsFloat(L"Distance");
		
	debug += L"\nDistance : " + FString::SanitizeFloat(distance);
	debug += L"\nAcceptable : " + FString::SanitizeFloat(AcceptableDistance);

	CLog::Print(debug, 0.1f, FColor::Green);

	if (distance < AcceptableDistance)
	{
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
				owner->GetCharacterMovement()->StopMovementImmediately();
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}

		else
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	else if(CurTimer >= ResetTime)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	CurTimer += DeltaSeconds;
}
