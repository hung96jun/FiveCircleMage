#include "AI/TaskNode/C_BTT_TestTask.h"
#include "Characters/C_Unit.h"
#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/CLog.h"

UC_BTT_TestTask::UC_BTT_TestTask()
{
	NodeName = L"TestTask";
}

EBTNodeResult::Type UC_BTT_TestTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetOwner() == nullptr) return EBTNodeResult::Failed;

	//AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetOwner());
	//if (controller == nullptr) return;
	//
	//AC_Unit* owner = Cast<AC_Unit>(controller->GetCharacter());
	//if (owner == nullptr) return;

	CLog::Print(L"TestTask", 10.0f, FColor::Blue);

	return EBTNodeResult::Succeeded;
}
