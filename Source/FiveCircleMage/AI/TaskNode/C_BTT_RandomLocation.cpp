#include "AI/TaskNode/C_BTT_RandomLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"
#include "Utilities/Defines.h"


UC_BTT_RandomLocation::UC_BTT_RandomLocation()
{
	NodeName = L"BTT_RandomLocation";
}

EBTNodeResult::Type UC_BTT_RandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACharacter* character = Cast<ACharacter>(controller->GetCharacter());
	CheckNullResult(character, EBTNodeResult::Failed);

	FVector location = character->GetActorLocation();
	UNavigationSystemV1* nav = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	CheckNullResult(nav, EBTNodeResult::Failed);

	FNavLocation navLocation;
	if (nav->GetRandomReachablePointInRadius(location, Radius, navLocation) == true)
	{
		controller->GetBlackboardComponent()->SetValueAsVector(BlackboardKey, navLocation);
	}

	return EBTNodeResult::Succeeded;
}
