#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "C_Monster.generated.h"

/**
 * 
 */
class UBehaviorTree;
class AC_WeaponBase;
class UWidgetComponent;
class UC_MonsterUI;

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AC_WeaponBase* Weapon = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UWidgetComponent* MonsterUI;

public:
	AC_Monster();

protected:
	virtual void BeginPlay()  override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetAttackNum(const int Num);
	const int GetAttackNum() const { return AttackNum; }

	const int GetMaxAttackNum() const { return MaxAttackNum; }
	const float GetAttackCoolTime() const { return AttackCoolTime; }
	const bool IsAttacking() const { return bAttacking; }

	void ResetAttackState();

	void SetTargetLocation(const FVector Value) { TargetLocation = Value; }

	UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	const float GetAttackRange() { return AttackRange; }

	//virtual void AttachWeapon(const FName BoneName, const FVector Offset);
	//virtual void OnAttacking();
	//virtual void EndAttacking();

	virtual void OnDeath() override;

	// 무기 할당 및 장착
	void AttachWeapon(AC_WeaponBase* Actor, const FName BoneName, const FVector Extent, const FVector Offset = FVector::ZeroVector);
	// 무기 소켓 변경
	void AttachWeapon(const FName BoneName, const FVector Offset);
	void OnAttacking();
	void EndAttacking();

	virtual void GetDmg(const float Dmg, const EUnitState Type) override;

private:
	int AttackNum = -1;

	UC_MonsterUI* HPBar = nullptr;
};
