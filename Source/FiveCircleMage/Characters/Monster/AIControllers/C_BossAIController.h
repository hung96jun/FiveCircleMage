#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_BossAIController.generated.h"

/**
 * 
 */
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;

class AC_Boss;
class AC_Mage;

UCLASS()
class FIVECIRCLEMAGE_API AC_BossAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackCoolTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enable")
		bool bEnableMeleeAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enable")
		bool bEnableRangedAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enable")
		bool bEnableShouting;

protected:
	UFUNCTION()
		void EndAttacking();

public:
	AC_BossAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	void OnAttacking();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	FTimerDelegate AttackTimerDelegate;
	FTimerHandle AttackTimerHandle;

	AC_Boss* Character = nullptr;
	AC_Mage* Target = nullptr;

	bool bAttacking = false;

	float MeleeCoolTime;
	float RangedCoolTime;
	float ShoutingCoolTime;
};
