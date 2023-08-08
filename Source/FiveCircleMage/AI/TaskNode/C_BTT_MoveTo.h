#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
//#include "BehaviorTree/BTTaskNode.h"
#include "C_BTT_MoveTo.generated.h"

/**
 * 
 */
UCLASS()
//class FIVECIRCLEMAGE_API UC_BTT_MoveTo : public UBTTask_MoveTo
class FIVECIRCLEMAGE_API UC_BTT_MoveTo : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FBlackboardKeySelector Target;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AcceptableRadius = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "Float type key"))
		FBlackboardKeySelector AcceptableKey;

public:
	UC_BTT_MoveTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
