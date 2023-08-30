#include "AI/Service/C_BTS_BossUpdateEnableMelee.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateEnableMelee::UC_BTS_BossUpdateEnableMelee()
{
	NodeName = L"BTS_BossUpdateEnableMelee";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateEnableMelee::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bEnableMeleeAttack", controller->GetEnableMeleeAttack());
}