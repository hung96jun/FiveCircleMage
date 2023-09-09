// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_BossUpdateDistance.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTS_BossUpdateDistance : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTS_BossUpdateDistance();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
