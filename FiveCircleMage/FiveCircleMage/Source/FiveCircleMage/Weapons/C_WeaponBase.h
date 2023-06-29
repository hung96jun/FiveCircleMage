#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_WeaponBase.generated.h"

class UStaticMesh;
class UMaterialInstance;

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
class FIVECIRCLEMAGE_API AC_WeaponBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UC_DamageComponent* DamageComp = nullptr;

public:	
	AC_WeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	float Damage = 0.0f;
};
