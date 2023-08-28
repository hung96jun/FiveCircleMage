#include "AI/Service/C_BTS_BossUpdateSecondPhase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateSecondPhase::UC_BTS_BossUpdateSecondPhase()
{
	NodeName = L"BTS_BossUpdateSecondPhase";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateSecondPhase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bOnSecondPhase", controller->GetSecondPhase());
}
