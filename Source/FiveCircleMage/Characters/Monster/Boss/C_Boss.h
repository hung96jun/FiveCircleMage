#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "C_Boss.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bOnSecondPhase = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		bool bIsDead = false;

public:
	AC_Boss();

	virtual void Tick(float DeltaTime) override;
	void Spawn(FVector3d SpawnLocation);

	const bool IsAttacking() { return bAttacking; }
	const float CurHPRate() { return UnitStatus.GetHPRate(); }

	virtual void GetDmg(const float Dmg, const EUnitState Type) override;

	void SetTarget(AActor* Actor) { Target = Actor; }

	void SetBehaviorTree(UBehaviorTree* BT, UBlackboardComponent* BB);

protected:
	virtual void BeginPlay() final;

private:
	void Init();

	void UpdateData(float DeltaTime);
	void SetValueAtBB();

	void BeginSecondPhase();

	void Dead();

public:
	void OnMeleeAttack();
	void OnRangedAttack();
	void OnSpawnedShout();
	void OnGroggy();

	void EndAttack() { bAttacking = false; }
	void EndMeleeAttack() { bMeleeAttacking = false; }
	void EndRangedAttack() { bRangedAttacking = false; }
	void EndSpawnedShout() { bSpawnedShouting = false; }

private:
	AActor* Target = nullptr;

	bool bIsActive = false;

	const float RangedAttackSpeed = 0.0f;
	float RangedAttackFrame = 0.0f;
	const float MeleeAttackSpeed = 10.0f;
	float MeleeAttackFrame = 0.0f;
	const float SpawnedShoutSpeed = 0.0f;
	float SpawnedShoutFrame = 0.0f;
	
	const float OriginGroggyArmor = 0.0f;
	float GroggyArmor = 0.0f;
	float GroggyArmorRegeneratedPower = 0.0f;

	int32 CurSpawnedMinions = 0;

	UBehaviorTree* BTAsset = nullptr;
	UBlackboardComponent* BBAsset = nullptr;
};