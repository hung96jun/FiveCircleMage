#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "C_MagicMes.generated.h"


/**
* 효과 없이 SpSkill(ex - Light);
*/
UCLASS()
class FIVECIRCLEMAGE_API AC_MagicMes : public AC_MagicSkill
{
	GENERATED_BODY()

public:
	AC_MagicMes();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;
	void SetDelayTime(float Time) { OriginDelayTime = Time; }

protected:
	//virtual void OnActive() {}
	virtual void EndActive();

protected:
	float OriginDelayTime;
	float DelayTime;
};
