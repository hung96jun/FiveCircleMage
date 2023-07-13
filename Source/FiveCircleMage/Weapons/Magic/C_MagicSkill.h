#pragma once

#include "CoreMinimal.h"
#include "Weapons/C_DamageBase.h"
#include "C_MagicSkill.generated.h"

class UCapsuleComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_MagicSkill : public AC_DamageBase
{
	GENERATED_BODY()

protected:
	// Particle
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particle")
		FString Key;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCapsuleComponent* Collision = nullptr;

protected:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AC_MagicSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void SetMagic(UParticleSystem* CopyParticle, FVector3d CollisionScale, float Dmg, EUnitState MagicProperty = EUnitState::Normal, float Speed = 0.0f);
	void SetCollisionSize(FVector3d CollisionSize);
	void PlayParticle();

protected:
	float MoveSpeed;
	FVector MoveDirection;

	UParticleSystem* Particle;

	EUnitState State;
};