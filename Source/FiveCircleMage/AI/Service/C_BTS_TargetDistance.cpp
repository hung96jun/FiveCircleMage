#include "AI/Service/C_BTS_TargetDistance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_AIControllerBase.h"
#include "Characters/C_Unit.h"

#include "Utilities/CLog.h"
#include "Utilities/Defines.h"

UC_BTS_TargetDistance::UC_BTS_TargetDistance()
{
	NodeName = L"BTS_TargetDistance";
	bNotifyTick = true;
}

void UC_BTS_TargetDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CLog::Print(L"Call Service TargetDistance", 1.0f, FColor::Blue);

	CheckNull(OwnerComp.GetAIOwner());

	AC_AIControllerBase* controller = Cast<AC_AIControllerBase>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNull(blackboard);

	AActor* targetActor = Cast<AActor>(blackboard->GetValueAsObject(L"Target"));
	CheckNull(targetActor);

	FVector location = controller->GetCharacter()->GetActorLocation();
	FVector target = targetActor->GetActorLocation();

	float distance = (target - location).Length();

	controller->GetBlackboardComponent()->SetValueAsFloat(L"Distance", distance);
	CLog::Print(L"Distance is : " + FString::SanitizeFloat(distance), 0.01f, FColor::Yellow);
}
