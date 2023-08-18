#pragma once

#include "CoreMinimal.h"
#include "Characters/Monster/C_Monster.h"
#include "C_Spider.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_Spider : public AC_Monster
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FPredictProjectilePathParams ProjectileParams;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ProjectileHeight = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ProjectileDistance = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bDebug = false;

public:
	AC_Spider();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void OnFireTrace();
	void OnFire();

private:
	bool bEnableTrace = false;
};
