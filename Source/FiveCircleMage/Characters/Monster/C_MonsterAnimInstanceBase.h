#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_MonsterAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_MonsterAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		float Direction = 0.0f;

	UPROPERTY(BlueprintReadOnly)
		bool bAttacking = false;

	UPROPERTY(BlueprintReadOnly)
		bool bDeath = false;

	UPROPERTY(BlueprintReadOnly)
		int AttackNum = 0;

public:
	UC_MonsterAnimInstanceBase();

	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	AC_Monster* Character = nullptr;
};
