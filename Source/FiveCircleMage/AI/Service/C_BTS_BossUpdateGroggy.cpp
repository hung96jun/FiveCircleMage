#include "AI/Service/C_BTS_BossUpdateGroggy.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateGroggy::UC_BTS_BossUpdateGroggy()
{
	NodeName = L"BTS_BossUpdateIsDead";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateGroggy::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bOnGroggy", controller->GetGroggy());
}