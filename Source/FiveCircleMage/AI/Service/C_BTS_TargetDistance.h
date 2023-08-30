#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_TargetDistance.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTS_TargetDistance : public UBTService
{
	GENERATED_BODY()
	
public:
	UC_BTS_TargetDistance();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	//virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
