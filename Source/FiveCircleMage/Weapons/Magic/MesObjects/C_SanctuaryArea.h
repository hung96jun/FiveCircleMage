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
	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AC_SanctuaryArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

protected:
	virtual void OnActive() {}
	virtual void EndActive();

};
