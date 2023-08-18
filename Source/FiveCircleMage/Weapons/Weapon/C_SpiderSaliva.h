#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon/C_WeaponBase.h"
#include "C_SpiderSaliva.generated.h"

/**
 * 
 */
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_SpiderSaliva : public AC_WeaponBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraSystem* Particle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraComponent* ParticleComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Precision;

public:
	AC_SpiderSaliva();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void OnFire(const FVector& Start, const FVector& Target);

private:
	void SetParabolation(const FVector& Start, const FVector& End);

private:
	const float Height = 500.0f;

	TArray<FVector> Routes;
};
