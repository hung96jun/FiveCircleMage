#include "AI/Service/C_BTS_BossUpdateAttacking.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateAttacking::UC_BTS_BossUpdateAttacking()
{
	NodeName = L"BTS_BossUpdateOnAttacking";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateAttacking::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bOnAttacking", controller->GetOnAttacking());
}