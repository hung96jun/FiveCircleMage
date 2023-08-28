#include "AI/Service/C_BTS_BossUpdateAttacking.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateAttacking::UC_BTS_BossUpdateAttacking()
{
	NodeName = L"BTS_BossUpdateOnAttacking";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateAttacking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bOnAttacking", controller->GetOnAttacking());
}