#include "AI/Service/C_BTS_BossUpdateSecondPhase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateSecondPhase::UC_BTS_BossUpdateSecondPhase()
{
	NodeName = L"BTS_BossUpdateSecondPhase";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateSecondPhase::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bOnSecondPhase", controller->GetSecondPhase());
}