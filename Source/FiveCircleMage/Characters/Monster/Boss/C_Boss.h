#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "C_Boss.generated.h"

class UBehaviorTree;

UCLASS()
class FIVECIRCLEMAGE_API AC_Boss : public AC_Unit
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float RangedAttackDistance = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bEnableRangedAttack = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bRangedAttacking = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bEnableSpawnedShout = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bSpawnedShouting = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MeleeAttackDistance = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bEnableMeleeAttack = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bMeleeAttacking = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float DistanceToTarget = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnGroggy = false;

public:
	AC_Boss();

	virtual void Tick(float DeltaTime) override;
	void Spawn(FVector3d SpawnLocation);

	const bool IsAttacking() { return bAttacking; }
	const float CurHPRate() { return UnitStatus.GetHPRate(); }

	virtual void GetDmg(const float Dmg, const EUnitState Type) override;

protected:
	virtual void BeginPlay() final;

private:
	void Init();

	void UpdateData(float DeltaTime);

	void MeleeAttack();
	void RangedAttack();
	void SpawnedShout();

private:
	bool bIsActive = false;

	float RangedAttackSpeed = 0.0f;
	float MeleeAttackSpeed = 0.0f;
	float SpawnedShoutSpeed = 0.0f;
	
	const float OriginGroggyArmor = 0.0f;
	float GroggyArmor = 0.0f;

	int32 CurSpawnedMinions = 0;
};