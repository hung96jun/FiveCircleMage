// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "C_MagicMissile.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_MagicMissile : public AC_MagicSkill
{
	GENERATED_BODY()
	
public:
	AC_MagicMissile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

private:
	void Move(float DeltaTime);

private:
	FVector MoveDirection;
};