#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MagicMes.h"
#include "C_LivingBoom.generated.h"

/**
 *
 */

UCLASS()
class FIVECIRCLEMAGE_API AC_LivingBoom : public AC_MagicMes
{
	GENERATED_BODY()

public:
	AC_LivingBoom();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnPatch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCapsuleComponent* PatchCollision = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

	void Boom();

	virtual void PlayParticle(int32 ParticleType = MAIN_PARTICLE) override;

	void SetSubParticle(UNiagaraSystem* Particle, FVector Location, FRotator Rotation) { SubParticle.SetParticle(Particle, Location, Rotation); }

	void SetTarget(AC_Unit* _Target);
	void SetMultple(int32 Count) { MultipleCount = Count * 2; }

private:
	void ActivePatchCollision(bool Active) { Active ? PatchCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly) : PatchCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); }

private:
	FParticleInfo SubParticle;

	TArray<AC_Unit*> UnitsInArea;
	AC_Unit* Target = nullptr;
	int32 MultipleCount;
};

