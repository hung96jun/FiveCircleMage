#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "C_MagicCoord.generated.h"

UCLASS()
class FIVECIRCLEMAGE_API AC_MagicCoord : public AC_MagicSkill
{
	GENERATED_BODY()
	
public:
	AC_MagicCoord();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

	void SetDelayTime(float Time) { OriginDelayTime = DelayTime; }

private:
	TArray<AC_Unit*> Targets;
	float OriginDelayTime;
	float DelayTime;
};
