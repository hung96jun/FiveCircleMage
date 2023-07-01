#pragma once

#include "CoreMinimal.h"
#include "Weapons/C_DamageBase.h"
#include "C_MagicSkill.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_MagicSkill : public AC_DamageBase
{
	GENERATED_BODY()

protected:
	// Particle
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particle")
		FString Key;

public:
	AC_MagicSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Spawn();
};
