#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/Weapon/C_WeaponBase.h"
#include "C_WeaponSpawnInfo.generated.h"

/**
 * 
 */
class AC_WeaponBase;

USTRUCT(BlueprintType)
struct FWeaponSpawnInfo
{
	GENERATED_BODY()

public:
	const FString GetName() const { return Name; }
	TSubclassOf<AActor> GetClass() { return Class; }
	const int GetMax() const { return Max; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Max = 0;
};

UCLASS()
class FIVECIRCLEMAGE_API UC_WeaponSpawnInfo : public UObject
{
	GENERATED_BODY()
	
};
