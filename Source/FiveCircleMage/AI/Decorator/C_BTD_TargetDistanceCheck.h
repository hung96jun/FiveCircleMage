#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "C_BTD_TargetDistanceCheck.generated.h"

/**
 * Compare Owner's AttackRange and the distance between Target and Owner
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTD_TargetDistanceCheck : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bFloatCompair = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CheckDistance = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FBlackboardKeySelector DistanceKey;

public:
	UC_BTD_TargetDistanceCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
