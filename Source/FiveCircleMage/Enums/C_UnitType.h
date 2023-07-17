#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_UnitType.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EUnitForceType : uint8
{
	None,
	Player,
	Monster,
};

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	Normal = 0,
	Slow = 1,
	Burn = 2,
	Stun = 3,

	Size = Stun,
	// ««»Ì
};

UCLASS()
class FIVECIRCLEMAGE_API UC_UnitType : public UObject
{
	GENERATED_BODY()

public:
	UC_UnitType();

	static FString EnumToString(const EUnitForceType  Value);
	static EUnitForceType StringToEnum(const FString Value);
	static uint8 StringToInt(const FString Value);
};

UCLASS()
class FIVECIRCLEMAGE_API UC_UnitState : public UObject
{
	GENERATED_BODY()

public:
	UC_UnitState();

	static FString EnumToString(const EUnitState  Value);
	static EUnitState StringToEnum(const FString Value);
	static uint8 StringToInt(const FString Value);
};