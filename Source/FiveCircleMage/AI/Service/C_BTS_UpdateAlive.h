#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_UpdateAlive.generated.h"

/**
 * 
 */
class AC_Unit;

UCLASS()
class FIVECIRCLEMAGE_API UC_BTS_UpdateAlive : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTS_UpdateAlive();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
