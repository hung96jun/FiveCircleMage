// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_BossUpdateAttacking.generated.h"

UCLASS()
class FIVECIRCLEMAGE_API UC_BTS_BossUpdateAttacking : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTS_BossUpdateAttacking();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
