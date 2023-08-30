#pragma once

#include "CoreMinimal.h"
#include "Characters/Monster/C_Monster.h"
#include "C_Bear.generated.h"

/**
 * 
 */
class AC_WeaponBase;

UCLASS()
class FIVECIRCLEMAGE_API AC_Bear : public AC_Monster
{
	GENERATED_BODY()

public:
	AC_Bear();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};