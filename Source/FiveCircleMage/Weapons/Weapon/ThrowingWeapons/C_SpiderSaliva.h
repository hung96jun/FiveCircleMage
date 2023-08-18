#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon/C_ThrowingWeapon.h"
#include "Enums/C_UnitType.h"
#include "C_SpiderSaliva.generated.h"

/**
 * 
 */
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_SpiderSaliva : public AC_ThrowingWeapon
{
	GENERATED_BODY()

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UNiagaraSystem* Particle;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UNiagaraComponent* ParticleComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* StaticMesh;

public:
	AC_SpiderSaliva();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//void OnFire(const FVector& Target);
	virtual void OnHitAction() override;
	virtual void SetActive(const bool Active) override;

};
