#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/MesObjects/C_MagicMes.h"
#include "C_MagicLight.generated.h"

/**
 * 
 */
class UPointLightComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_MagicLight : public AC_MagicMes
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UPointLightComponent* Light = nullptr;

public:
	AC_MagicLight();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator);

protected:
	virtual void EndActive();

};
