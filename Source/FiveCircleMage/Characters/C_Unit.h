#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Utilities/Defines.h"
#include "Components/CapsuleComponent.h"
#include "Enums/C_UnitType.h"
#include "Structs/C_DebuffInfo.h"
#include "GenericTeamAgentInterface.h"
#include "C_Unit.generated.h"


class UCapsuleComponent;

USTRUCT(BlueprintType)
struct FUnitStatus
{
	GENERATED_USTRUCT_BODY()

public:
	FUnitStatus() {}
	FUnitStatus(const float HP, const float MoveSpeed)
		:OriginHP(HP), OriginMoveSpeed(MoveSpeed),
		CurHP(HP), CurMoveSpeed(MoveSpeed)
	{
	}

	void InitStatus()
	{
		CurHP = OriginHP;
		CurMoveSpeed = OriginMoveSpeed;
	}

	float* GetOriginHP() { return &OriginHP; }
	const float GetOriginMoveSpeed() const { return OriginMoveSpeed; }

	float* GetCurHP() { return &CurHP; }
	const float GetCurMoveSpeed() const { return CurMoveSpeed; }

	void GetDmg(const float Dmg) { CurHP = Dmg; }
	void DecreaseMoveSpeed(const float Percent) { CurMoveSpeed = OriginMoveSpeed * (1 - Percent); }
	void ResetMoveSpeed() { CurMoveSpeed = OriginMoveSpeed; }

	const bool IsDeath() { return CurHP < 0.0f; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float OriginHP = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float OriginMoveSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHP = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurMoveSpeed = 0.0f;
};

UCLASS()
class FIVECIRCLEMAGE_API AC_Unit : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
		EUnitForceType UnitType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
		FUnitStatus UnitStatus;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
		TArray<EUnitState> UnitStates;

private:
	UFUNCTION()
		void ClearDebuffTimerHandle(const int Index);

public:
	AC_Unit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override {}

	virtual void GetDmg(const float Dmg, const EUnitState Type);
	virtual void GetHeal(const float Amount) {}
	virtual void Death() {}

	FUnitStatus* GetUnitStatus() { return &UnitStatus; }

	void SetDebuffHandle(const int Index, FTimerDelegate& Delegate, const FDebuffInfo Info);
	const bool IsDebuffActive(const int Index) { return DebuffHandle[Index].IsActive(); }
	FDebuffHandle* GetDebuffHandles() { return DebuffHandle; }

	void DecreaseMoveSpeed(float Percent);
	void ResetMoveSpeed();

	const EUnitForceType GetForceType() { return ForceType; }

	virtual FGenericTeamId GetGenericTeamId() const final
	{
		return GenericTeamID;
	}

protected:
	FGenericTeamId GenericTeamID;
	FDebuffHandle DebuffHandle[CAST(int, EUnitState::Size)];

	EUnitForceType ForceType;

	bool bAttacking = false;
};
