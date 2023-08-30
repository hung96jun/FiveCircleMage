// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/C_BTS_BossUpdateIsDead.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Utilities/Defines.h"

UC_BTS_BossUpdateIsDead::UC_BTS_BossUpdateIsDead()
{
	NodeName = L"BTS_BossUpdateIsDead";
	bNotifyOnSearch = true;
}

void UC_BTS_BossUpdateIsDead::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckNull(SearchData.OwnerComp.GetAIOwner());

	AC_BossAIController* controller = Cast <AC_BossAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(controller);

	controller->GetBlackboardComponent()->SetValueAsBool(L"bIsDead", controller->GetIsDead());
}