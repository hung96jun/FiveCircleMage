#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "C_Boss.generated.h"

/**
 * 
 */
class UBehaviorTree;

UCLASS()
class FIVECIRCLEMAGE_API AC_Boss : public AC_Unit
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		AC_Unit* Target = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackRange = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackCoolTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnRangedAttacking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnMeleeAttacking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnShouting;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnGroggy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnMove;

public:
	AC_Boss();

	void SetAttackNum(const int Num);

	const float GetAttackCoolTime() const { return AttackCoolTime; }
	const bool IsAttacking() const { return bAttacking; }

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

	UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	const float GetAttackRange() { return AttackRange; }
	void SetTarget(AC_Unit* _Target) { Target = _Target; }
};