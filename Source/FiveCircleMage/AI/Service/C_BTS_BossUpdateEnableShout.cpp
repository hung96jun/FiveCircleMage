#include "AI/Service/C_BTS_BossUpdateEnableShout.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateEnableShout::UC_BTS_BossUpdateEnableShout()
{
	NodeName = L"BTS_BossUpdateEnableShout";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateEnableShout::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bEnableShouting", controller->GetEnableSpawnedShout());
}