#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "C_Monster.generated.h"

/**
 * 
 */
class UBehaviorTree;

UCLASS()
class FIVECIRCLEMAGE_API AC_Monster : public AC_Unit
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxAttackNum = -1;

public:
	AC_Monster();

	const int GetMaxAttackNum() const { return MaxAttackNum; }
	void SetAttackNum(const int Num);

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

	UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

private:
	int AttackNum = -1;
};
