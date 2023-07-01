#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_CastingElement.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECastingElement : uint8
{
	None,
	Fire,
	Ice,
	Light,
	Dark,
};

UCLASS()
class FIVECIRCLEMAGE_API UC_CastingElement : public UObject
{
	GENERATED_BODY()

public:
	UC_CastingElement();

	static FString EnumToString(const ECastingElement  Value);

	static uint8 StringToInt(const FString Value);
};
