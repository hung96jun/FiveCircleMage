#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Unit.h"
#include "C_Monster.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_Monster : public AC_Unit
{
	GENERATED_BODY()

public:
	AC_Monster();

protected:
	virtual void BeginPlay() final;

public:
	virtual void Tick(float DeltaTime) final;

};
