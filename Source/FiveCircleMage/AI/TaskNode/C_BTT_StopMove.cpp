#include "AI/TaskNode/C_BTT_StopMove.h"

#include "Characters/C_Unit.h"
#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/Defines.h"

UC_BTT_StopMove::UC_BTT_StopMove()
{
	NodeName = L"BTT_StopMove";
}

EBTNodeResult::Type UC_BTT_StopMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	AC_Unit* owner = Cast<AC_Unit>(controller->GetCharacter());
	CheckNullResult(owner, EBTNodeResult::Failed);

	owner->GetCharacterMovement()->StopMovementImmediately();

	return EBTNodeResult::Succeeded;
}
