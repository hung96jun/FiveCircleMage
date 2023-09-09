#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon/C_ThrowingWeapon.h"
#include "C_BossRock.generated.h"

UCLASS()
class FIVECIRCLEMAGE_API AC_BossRock : public AC_ThrowingWeapon
{
	GENERATED_BODY()
		
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UStaticMeshComponent* MeshComp;

public:
	AC_BossRock();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void OnFire(const FVector& Target, AC_Unit* Actor);
	virtual void OnHitAction() override;

	virtual void SetActive(const bool Value);

private:
	FVector FireDirection;
	const float OriginSpeed = 50.0f;
	float Speed = OriginSpeed;

	const float OriginAccelatingInterval = 30.0f;
	float AccelatingInterval = OriginSpeed;

	const float MaxLifeTime = 5.0f;
	float CurLifeTime = 0.0f;
};
