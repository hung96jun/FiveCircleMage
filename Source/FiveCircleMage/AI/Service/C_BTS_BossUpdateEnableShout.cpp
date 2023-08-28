#include "AI/Service/C_BTS_BossUpdateEnableShout.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateEnableShout::UC_BTS_BossUpdateEnableShout()
{
	NodeName = L"BTS_BossUpdateEnableShout";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateEnableShout::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bEnableShouting", controller->GetEnableSpawnedShout());
}
