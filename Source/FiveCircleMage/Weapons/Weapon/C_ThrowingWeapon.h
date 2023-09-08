#pragma once

#include "CoreMinimal.h"
#include "Weapons/C_DamageBase.h"
#include "C_ThrowingWeapon.generated.h"

/**
 * 
 */
class UCapsuleComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_ThrowingWeapon : public AC_DamageBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCapsuleComponent* Collision = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Velocity = FVector::ZeroVector;

public:
	AC_ThrowingWeapon();

public:
	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnFire(const FVector& Target, AC_Unit* Actor);
	virtual void OnHitAction();

	virtual void SetActive(const bool Active) override;

};
