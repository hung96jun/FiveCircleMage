#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MagicDamagedMes.h"
#include "C_VampiricAreaSkill.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_VampiricAreaSkill : public AC_MagicDamagedMes
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HealAmount = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DelayTime = 0.5f;

protected:
	UFUNCTION()
		void OnActive();

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AC_VampiricAreaSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

protected:
	virtual void EndActive();

};
