// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_BossUpdateEnableMelee.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTS_BossUpdateEnableMelee : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTS_BossUpdateEnableMelee();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
