// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/C_BTS_BossUpdateIsDead.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateIsDead::UC_BTS_BossUpdateIsDead()
{
	NodeName = L"BTS_BossUpdateIsDead";
	bNotifyTick = true;
}

void UC_BTS_BossUpdateIsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bIsDead", controller->GetIsDead());
}
