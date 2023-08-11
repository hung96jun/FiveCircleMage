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

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNullResult(blackboard, false);

	float targetDistance = blackboard->GetValueAsFloat("Distance");

	bool result = false;
	if (bFloatCompair == true)
		return targetDistance < CheckDistance;

	else
	{
		float compairDistance = blackboard->GetValueAsFloat(DistanceKey.SelectedKeyName);
		return targetDistance < compairDistance;
	}

	return false;
}
