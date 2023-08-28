#include "AI/Service/C_BTS_BossUpdateGroggy.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateGroggy::UC_BTS_BossUpdateGroggy()
{
	NodeName = L"BTS_BossUpdateIsDead";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateGroggy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bOnGroggy", controller->GetGroggy());
}
