#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "Weapons/Weapon/C_WeaponBase.h"
#include "Structs/C_ParticleInfo.h"
#include "C_Boss.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class UC_BossUI;

UCLASS()
class FIVECIRCLEMAGE_API AC_Boss : public AC_Unit
{
	GENERATED_BODY()

protected:
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 SpawnAmount = 2;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float GroggyArmor = 0.0f;

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
	void NaturalHeal(float DeltaTime);

	void UpdateData(float DeltaTime);

	void BeginSecondPhase();

	void Dead();

public:
	void Init();
	void WeaponChangeBone(FName BoneName, FVector OffsetLocation = FVector::ZeroVector, FRotator OffsetRotation = FRotator::ZeroRotator);

	void OnMeleeAttack();
	void OnRangedAttack();
	void OnSpawnedShout();
	void OnGroggy();

	void EndAttack() { bAttacking = false; }
	void EndMeleeAttack() { bMeleeAttacking = false; MeleeAttackNum = 0; }
	void EndWeaponCollision() { Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision); }
	void EndRangedAttack() { bRangedAttacking = false; }
	void EndSpawnedShout() { bSpawnedShouting = false; }
	void EndGroggy() { bOnGroggy = false; GroggyArmor = OriginGroggyArmor; }

	// Update and return datas for updating blackboard
	bool GetEnableMeleeAttack() { return bEnableMeleeAttack; }
	bool GetEnableRangedAttack() { return bEnableRangedAttack; }
	bool GetEnableSpawnedShout() { return bEnableSpawnedShout; }
	bool GetGroggy() { return bOnGroggy; }
	float GetHPRate() { return CurHPRate(); }
	bool GetSecondPhase() { return bOnSecondPhase; }
	bool GetIsDead() { return bIsDead; }
	bool GetOnAttacking() { return bAttacking; }

	bool GetMeleeAttack() { return bMeleeAttacking; }
	bool GetRangedAttack() { return bRangedAttacking; }
	bool GetSpawnedShouting() { return bSpawnedShouting; }

	const int GetMeleeAttackNum() { return MeleeAttackNum; }

	bool IsArmorFull() { return GroggyArmor >= OriginGroggyArmor; }

	float* GetArmor() { return &GroggyArmor; }
	const float GetOriginArmor() { return OriginGroggyArmor; }

	void SetUI(UC_BossUI* UI) { BossUI = UI; }

private:
	AActor* Target = nullptr;

	bool bIsActive = false;

	const float RangedAttackSpeed = 10.0f;
	float RangedAttackFrame = 0.0f;
	const float MeleeAttackSpeed = 7.0f;
	float MeleeAttackFrame = 0.0f;
	const float SpawnedShoutSpeed = 30.0f;
	float SpawnedShoutFrame = 0.0f;

	const float OriginGroggyArmor = 150.0f;
	float GroggyArmorRegeneratedPower = 40.0f;

	const int MaxMeleeAttackNum = 3;
	int MeleeAttackNum = 0;

	int32 CurSpawnedMinions = 0;

	UBehaviorTree* BTAsset = nullptr;
	UBlackboardComponent* BBAsset = nullptr;

	AC_WeaponBase* Weapon;

	UC_BossUI* BossUI = nullptr;
	TArray<FParticleInfo> ParticleInfos;
};