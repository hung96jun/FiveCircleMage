#include "AI/Service/C_BTS_BossUpdateEnableRanged.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateEnableRanged::UC_BTS_BossUpdateEnableRanged()
{
	NodeName = L"BTS_BossUpdateEnableRanged";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateEnableRanged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bEnableRangedAttack", controller->GetGroggy());
}
