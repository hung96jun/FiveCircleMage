// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/C_BTS_BossUpdateDistance.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateDistance::UC_BTS_BossUpdateDistance()
{
	NodeName = L"BTS_BossUpdateDistance";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNull(blackboard);

	AActor* targetActor = Cast<AActor>(blackboard->GetValueAsObject(L"Target"));
	CheckNull(targetActor);

	FVector ownerLocation = controller->GetCharacter()->GetActorLocation();
	FVector targetLocation = targetActor->GetActorLocation();

	float distance = (targetLocation - ownerLocation).Length();

	controller->GetBlackboardComponent()->SetValueAsFloat(L"Distance", distance);
}
