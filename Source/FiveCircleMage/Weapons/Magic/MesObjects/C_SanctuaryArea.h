#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MagicMes.h"
#include "C_SanctuaryArea.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_SanctuaryArea : public AC_MagicMes
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> EffectClass;

protected:
	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AC_SanctuaryArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

	void SetLaunchPower(const float Power) { MaxPower = Power; }

protected:
	virtual void OnActive() {}
	virtual void EndActive();

private:
	AActor* EffectActor = nullptr;
	float Radius = 400.0f;
	float MaxPower = 3500.0f;
};
