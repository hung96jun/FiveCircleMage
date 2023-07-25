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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAISenseConfig_Sight* SensingSight;

public:
	UFUNCTION()
		void OnSensingTarget(AActor* Actor, FAIStimulus Stimulus);

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
	AC_Monster* Character = nullptr;
};
