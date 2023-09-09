#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enums/C_Direction.h"
#include "C_PlayerAnimInstance.generated.h"

/**
 * 
 */

class AC_Mage;

UCLASS()
class FIVECIRCLEMAGE_API UC_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MoveSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsCasting = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsAttacking = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsDash = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EDirectionState DirectionState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsDeath = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bCasting = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bCastingBreak = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bOnFire = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bDeath = false;

public:
	UC_PlayerAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	AC_Mage* Character = nullptr;	
};
