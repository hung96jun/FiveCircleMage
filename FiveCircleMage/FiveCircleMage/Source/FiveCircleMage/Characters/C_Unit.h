#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Enums/C_UnitType.h"
#include "C_Unit.generated.h"

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

	const float GetOriginHP() const { return OriginHP; }
	const float GetOriginMoveSpeed() const { return OriginMoveSpeed; }

	const float GetCurHP() const { return CurHP; }
	const float GetCurMoveSpeed() const { return CurMoveSpeed; }

	void GetDmg(const float Dmg) { CurHP = Dmg; }
	void DecreaseMoveSpeed(const float Percent) { CurMoveSpeed = OriginMoveSpeed * (1 - Percent); }
	void ResetMoveSpeed() { CurMoveSpeed = OriginMoveSpeed; }

	const bool IsDeath() { return CurHP < 0.0f; }

private:
	float OriginHP;
	float OriginMoveSpeed;

	float CurHP;
	float CurMoveSpeed;
};

UCLASS()
class FIVECIRCLEMAGE_API AC_Unit : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
		EUnitForceType UnitType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
		FUnitStatus UnitStatus;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
		EUnitState UnitState;

public:
	AC_Unit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override {}

	virtual void GetDmg(const float Dmg, const EUnitState Type);
	virtual void Death() {}
};
