#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MesObject.h"
#include "C_DamagedMesObject.generated.h"

/**
 * 
 */
class AC_Unit;

UCLASS()
class FIVECIRCLEMAGE_API AC_DamagedMesObject : public AC_MesObject
{
	GENERATED_BODY()

public:
	AC_DamagedMesObject();

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
