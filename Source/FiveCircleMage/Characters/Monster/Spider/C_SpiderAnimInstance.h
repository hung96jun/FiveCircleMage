#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_SpiderAnimInstance.generated.h"

/**
 * 
 */
class AC_Monster;

UCLASS()
class FIVECIRCLEMAGE_API UC_SpiderAnimInstance : public UAnimInstance
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

public:
	UC_SpiderAnimInstance();

	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	AC_Monster* Character = nullptr;
};
