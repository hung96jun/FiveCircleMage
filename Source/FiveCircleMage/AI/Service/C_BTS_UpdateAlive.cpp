#include "AI/Service/C_BTS_UpdateAlive.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/C_Unit.h"
#include "Characters/Monster/AIControllers/C_AIControllerBase.h"

#include "Utilities/Defines.h"
#include "Utilities/CLog.h"


UC_BTS_UpdateAlive::UC_BTS_UpdateAlive()
{
	NodeName = L"BTS_UpdateAlive";
	bNotifyOnSearch = true;
	bNotifyTick = false;
}

void UC_BTS_UpdateAlive::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	AC_Unit* owner = Cast<AC_Unit>(controller->GetCharacter());
	CheckNull(owner);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNull(blackboard);

	CLog::Print(L"UpdateAlive", 0.01f, FColor::Cyan);

	if ((*owner->GetUnitStatus()->GetCurHP()) > 0.0f)
		blackboard->SetValueAsBool(L"bAlive", true);
	else
		blackboard->SetValueAsBool(L"bAlive", false);
}

void UC_BTS_UpdateAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());
	
	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	AC_Unit* owner = Cast<AC_Unit>(controller->GetCharacter());
	CheckNull(owner);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNull(blackboard);

	if ((*owner->GetUnitStatus()->GetCurHP()) > 0.0f)
		blackboard->SetValueAsBool(L"bAlive", true);
	else
		blackboard->SetValueAsBool(L"bAlive", false);
}
