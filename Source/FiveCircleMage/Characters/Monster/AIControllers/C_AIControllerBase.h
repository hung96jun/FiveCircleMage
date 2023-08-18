#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_AIControllerBase.generated.h"

/**
 * 
 */
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;

class AC_Monster;

UCLASS()
class FIVECIRCLEMAGE_API AC_AIControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UAIPerceptionComponent* AIPerceptionComponent;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UAISenseConfig_Sight* SensingSight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackCoolTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxAttackNum = 0;
//
//public:
//	UFUNCTION()
//		void OnSensingTarget(AActor* Actor, FAIStimulus Stimulus);

protected:
	UFUNCTION()
		void EndAttacking();

public:
	AC_AIControllerBase();

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

	AC_Monster* Character = nullptr;

	bool bAttacking = false;
};
