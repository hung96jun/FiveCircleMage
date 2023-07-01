#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_WeaponBase.generated.h"

class UStaticMesh;
class UMaterialInstance;

UCLASS()
class FIVECIRCLEMAGE_API AC_WeaponBase : public AActor
{
	GENERATED_BODY()

public:	
	AC_WeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Spawn();
};
