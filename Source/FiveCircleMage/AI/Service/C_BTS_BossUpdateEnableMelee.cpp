#include "AI/Service/C_BTS_BossUpdateEnableMelee.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateEnableMelee::UC_BTS_BossUpdateEnableMelee()
{
	NodeName = L"BTS_BossUpdateEnableMelee";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateEnableMelee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bEnableMeleeAttack", controller->GetGroggy());
}