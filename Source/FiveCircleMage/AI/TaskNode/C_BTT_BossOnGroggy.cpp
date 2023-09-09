// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/C_BTT_BossOnGroggy.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Characters/Monster/Boss/C_Boss.h"

#include "Utilities/Defines.h"

UC_BTT_BossOnGroggy::UC_BTT_BossOnGroggy()
{
	NodeName = L"BTT_BossOnGroggy";

	bNotifyTick = true;
}

EBTNodeResult::Type UC_BTT_BossOnGroggy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	CheckNullResult(OwnerComp.GetAIOwner(), EBTNodeResult::Failed);

	AC_BossAIController* controller = Cast<AC_BossAIController>(OwnerComp.GetAIOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	AC_Boss* owner = Cast<AC_Boss>(controller->GetCharacter());
	CheckNullResult(owner, EBTNodeResult::Failed);

	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	CheckNullResult(blackboard, EBTNodeResult::Failed);

	owner->OnGroggy();

	return EBTNodeResult::Succeeded;
}
