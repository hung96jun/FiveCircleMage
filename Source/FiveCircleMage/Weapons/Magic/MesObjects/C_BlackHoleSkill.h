#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MagicDamagedMes.h"
#include "C_BlackHoleSkill.generated.h"

/**
 * 
 */
enum class EBlackHoleState
{
	None,
	Inhalation,
	Flash,
	Explosion,
};

UCLASS()
class FIVECIRCLEMAGE_API AC_BlackHoleSkill : public AC_MagicDamagedMes
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraSystem* FlashEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float InhalationHeight = 50.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float InhalationDamage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ExplosionDamage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FlashDelay = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DelayTime = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float CurTime = 0.0f;

protected:
	UFUNCTION()
		void OnActive();

	UFUNCTION()
		void ChangeState();

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AC_BlackHoleSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

	virtual void SetMagic(UNiagaraSystem* CopyMainParticle, FVector CopyMainLocation, FRotator CopyMainRotation,
		UNiagaraSystem* CopyEndParticle, FVector CopyEndLocation, FRotator CopyEndRotation,
		float Dmg, ESkillType Type, float LifeTime = 5.0f, EUnitState MagicProperty = EUnitState::Normal, float Speed = 0.0f) override;

private:
	void OnInhalation();
	void OnExplosion();

protected:
	virtual void EndActive();

private:
	FTimerHandle ChangeTimerHandle;
	FTimerDelegate ChangeTimerDelegate;

	EBlackHoleState BlackHoleState;
};
