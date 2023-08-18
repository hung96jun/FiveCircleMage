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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		int MaxAttackNum = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackRange = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackCoolTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
		FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
		float LineDistance = 1000.0f;

public:
	AC_Monster();

	void SetAttackNum(const int Num);

	const int GetMaxAttackNum() const { return MaxAttackNum; }
	const float GetAttackCoolTime() const { return AttackCoolTime; }
	const bool IsAttacking() const { return bAttacking; }

	void ResetAttackState();

	void SetTargetLocation(const FVector Value) { TargetLocation = Value; }

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

	UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	const float GetAttackRange() { return AttackRange; }

private:
	int AttackNum = -1;
};
