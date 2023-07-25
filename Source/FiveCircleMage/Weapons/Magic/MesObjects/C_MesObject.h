#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "C_MesObject.generated.h"


/**
* 효과 없이 SpSkill(ex - Light);
*/
UCLASS()
class FIVECIRCLEMAGE_API AC_MesObject : public AC_MagicSkill
{
	GENERATED_BODY()

public:
	AC_MesObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;
	void SetDelayTime(float Time) { OriginDelayTime = DelayTime; }

protected:
	//virtual void OnActive() {}
	virtual void EndActive();

private:
	float OriginDelayTime;
	float DelayTime;
};
