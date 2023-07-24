#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MagicMes.h"
#include "C_MagicDamagedMes.generated.h"

/**
 * 
 */
class AC_Unit;

UCLASS()
class FIVECIRCLEMAGE_API AC_MagicDamagedMes : public AC_MagicMes
{
	GENERATED_BODY()

public:
	AC_MagicDamagedMes();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

protected:
	//virtual void OnActive() {}
	virtual void EndActive();

protected:
	FTimerHandle DamageTimerHandle;
	FTimerDelegate DamageTimerDelegate;

	float DamageInterval = 0.0f;
	TArray<AC_Unit*> OtherUnits;
};
