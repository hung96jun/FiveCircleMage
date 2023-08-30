// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_BossAnimInstance.generated.h"

/**
 * 
 */
class AC_Boss;

UCLASS()
class FIVECIRCLEMAGE_API UC_BossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		
protected:
	UPROPERTY(BlueprintReadOnly)
		bool bAttacking = false;

	UPROPERTY(BlueprintReadOnly)
		bool bOnGroggy = false;

	UPROPERTY(BlueprintReadOnly)
		bool bIsDead = false;

	UPROPERTY(BlueprintReadOnly)
		bool bMeleeAttacking = false;

	UPROPERTY(BlueprintReadOnly)
		bool bRangedAttacking = false;

	UPROPERTY(BlueprintReadOnly)
		bool bSpawnedShouting = false;

	UPROPERTY(BlueprintReadOnly)
		float Speed = false;
	
public:
	UC_BossAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	AC_Boss* Character = nullptr;
};
