#include "AI/Decorator/C_BTD_IsAlive.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/C_Unit.h"
#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/Defines.h"

UC_BTD_IsAlive::UC_BTD_IsAlive()
{
	NodeName = L"BTD_IsAlive";
}

bool UC_BTD_IsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), false);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, false);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNullResult(blackboard, false);

	//AC_Unit* owner = Cast<AC_Unit>(controller->GetCharacter());
	//CheckNullResult(owner, false);

	//if ((*owner->GetUnitStatus()->GetCurHP()) > 0.0f)
	//	return true;

	if (blackboard->GetValueAsBool(L"bAlive"))
		return true;

	return false;
}
