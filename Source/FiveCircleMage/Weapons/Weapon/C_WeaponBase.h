#pragma once

#include "CoreMinimal.h"
#include "Weapons/C_DamageBase.h"
#include "C_WeaponBase.generated.h"

class UStaticMesh;
class UMaterialInstance;

class UCapsuleComponent;

UCLASS()
class FIVECIRCLEMAGE_API AC_WeaponBase : public AC_DamageBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCapsuleComponent* Collision = nullptr;

protected:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	AC_WeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetActive(const bool Active) override;

};
