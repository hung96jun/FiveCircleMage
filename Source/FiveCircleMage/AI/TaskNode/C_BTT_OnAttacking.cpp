#include "AI/TaskNode/C_BTT_OnAttacking.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"
#include "Utilities/Defines.h"

UC_BTT_OnAttacking::UC_BTT_OnAttacking()
{
	NodeName = "BTT_OnAttacking";
}

EBTNodeResult::Type UC_BTT_OnAttacking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	controller->OnAttacking();

	return EBTNodeResult::Succeeded;
}
