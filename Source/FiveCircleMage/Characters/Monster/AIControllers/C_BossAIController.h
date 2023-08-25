#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/Monster/Boss/C_Boss.h"
#include "C_BossAIController.generated.h"

/**
 * 
 */

class UBehaviorTree;

UCLASS()
class FIVECIRCLEMAGE_API AC_BossAIController : public AAIController
{
	GENERATED_BODY()

public:
	AC_BossAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	AC_Boss* Character = nullptr;
	UBehaviorTree* BTAsset = nullptr;
};
