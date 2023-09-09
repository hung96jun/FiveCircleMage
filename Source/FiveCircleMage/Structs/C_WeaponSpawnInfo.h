#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Enums/C_UnitType.h"
//#include "Engine/StaticMesh.h"
////#include "Materials/Material.h"
//#include "Materials/MaterialInstance.h"
//#include "NiagaraSystem.h"
#include "C_WeaponSpawnInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponSpawnInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	const FString GetName() const { return Name; }
	TSubclassOf<AActor> GetClass() { return Class; }
	const int GetMax() const { return Max; }
	const float GetDamage() const { return Damage; }
	const float GetDamageFactor() const { return DamageFactor; }
	const EUnitState GetDebuffType() const { return DebuffType; }

	//UStaticMesh* GetStaticMesh() { return Mesh; }
	//TArray<UMaterialInstance*> GetMaterials() { return Materials; }
	//UNiagaraSystem* GetNiagara() { return Niagara; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Max = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 1.00, UIMin = 1.00))
		float DamageFactor = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EUnitState DebuffType = EUnitState::Normal;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UStaticMesh* Mesh = nullptr;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	TArray<UMaterialInstance*> Materials;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UNiagaraSystem* Niagara;
};

UCLASS()
class FIVECIRCLEMAGE_API UC_WeaponSpawnInfo : public UObject
{
	GENERATED_BODY()
	
};
