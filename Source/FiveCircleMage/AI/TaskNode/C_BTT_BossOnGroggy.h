// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTT_BossOnGroggy.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTT_BossOnGroggy : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UC_BTT_BossOnGroggy();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	AActor* TargetActor = nullptr;
};