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
	NoneType,
	Player,
	Monster,
};

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	None = 0,
	Normal = 4,
	Slow = 5,
	Burn = 6,
	Stun = 7,
	// ««»Ì
};

UCLASS()
class FIVECIRCLEMAGE_API UC_UnitType : public UObject
{
	GENERATED_BODY()
	
public:
	UC_UnitType();

	static FString EnumToString(const EUnitForceType  Value);
	static FString EnumToString(const EUnitState  Value);

	static uint8 StringToInt(const FString Value);
};
