#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTT_TestTask.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTT_TestTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BTT_TestTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
