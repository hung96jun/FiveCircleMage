#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DamageBase.generated.h"

class UC_DamageComponent;

USTRUCT(BlueprintType)
struct FWeaponInformation
{
	GENERATED_USTRUCT_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<UMaterialInstance*> Materials;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;
};

USTRUCT(BlueprintType)
struct FMagicInformation
{
	GENERATED_USTRUCT_BODY()

protected:

};

UCLASS()
class FIVECIRCLEMAGE_API AC_DamageBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UC_DamageComponent* DamageComp = nullptr;

protected:
	float Damage = 0.0f;

public:
	AC_DamageBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetActive(const bool Value) { bActive = Value; }
	const bool IsActive() { return bActive; }

protected:
	void Spawn(const FVector Location, const FRotator Rotation = FRotator::ZeroRotator) {}
	
protected:
	bool bActive = false;
};
