#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTT_RandomLocation.generated.h"

/**
 * Generate random coordinates of a certain radius based 
 * on your location using a NavgationMesh
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_BTT_RandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Radius = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName BlackboardKey = "MoveToLocation";

public:
	UC_BTT_RandomLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
