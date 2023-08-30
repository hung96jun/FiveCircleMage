#include "AI/Service/C_BTS_BossUpdateEnableRanged.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateEnableRanged::UC_BTS_BossUpdateEnableRanged()
{
	NodeName = L"BTS_BossUpdateEnableRanged";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateEnableRanged::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bEnableRangedAttack", controller->GetEnableRangedAttack());
}