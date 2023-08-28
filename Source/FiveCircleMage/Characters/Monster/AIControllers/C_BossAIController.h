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

	// Update and return datas for updating blackboard
	bool GetEnableMeleeAttack() { return Character->GetEnableMeleeAttack(); }
	bool GetEnableRangedAttack() { return Character->GetEnableRangedAttack(); }
	bool GetEnableSpawnedShout() { return Character->GetEnableSpawnedShout(); }
	bool GetGroggy() { return Character->GetGroggy(); }
	float GetHPRate() { return Character->GetHPRate(); }
	bool GetSecondPhase() { return Character->GetSecondPhase(); }
	bool GetIsDead() { return Character->GetIsDead(); }
	bool GetOnAttacking() { return Character->GetOnAttacking(); }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	AC_Boss* Character = nullptr;
	UBehaviorTree* BTAsset = nullptr;
};
