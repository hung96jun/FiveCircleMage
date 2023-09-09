// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_BossUpdateEnableRanged.generated.h"

UCLASS()
class FIVECIRCLEMAGE_API UC_BTS_BossUpdateEnableRanged : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTS_BossUpdateEnableRanged();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
