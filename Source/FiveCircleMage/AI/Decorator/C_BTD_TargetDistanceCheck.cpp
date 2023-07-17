#include "AI/Decorator/C_BTD_TargetDistanceCheck.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"
#include "Utilities/Defines.h"

UC_BTD_TargetDistanceCheck::UC_BTD_TargetDistanceCheck()
{
	NodeName = L"BTD_TargetDistanceCheck";
}

bool UC_BTD_TargetDistanceCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), false);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, false);

	ACharacter* character = controller->GetCharacter();
	CheckNullResult(character, false);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNullResult(blackboard, false);

	float attackRange = blackboard->GetValueAsFloat("AttackRange");

	AActor* target = Cast<AActor>(blackboard->GetValueAsObject("Target"));
	CheckNullResult(target, false);

	float distance = FVector(character->GetActorLocation() - target->GetActorLocation()).Size();

	return distance < attackRange;
}
