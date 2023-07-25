#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_SkillType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESkillType : uint8
{
    None,
    Missile,
    Beam,
    InPlace,
    Coord,
    Mes,
    Self,

    Last = Self,
};

UCLASS()
class FIVECIRCLEMAGE_API UC_SkillType : public UObject
{
	GENERATED_BODY()

public:
	static FString EnumToString(const ESkillType  Value);
	static uint8 StringToInt(const FString Value);
};
