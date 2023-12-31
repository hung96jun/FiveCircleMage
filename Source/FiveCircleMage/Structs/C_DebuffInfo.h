#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/C_UnitType.h"
#include "C_DebuffInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDebuffHandle
{
	GENERATED_USTRUCT_BODY()

public:
	FDebuffHandle() {}
	FDebuffHandle(EUnitState Type, FTimerHandle DebuffHandle, FTimerHandle FinHandle)
		: Debuff(Type), DebuffTimerHandle(DebuffHandle), DebuffFinTimerHandle(FinHandle) {}

	void SetDebuffTimerHandle(FTimerHandle Handle, FTimerHandle FinHandle)
	{
		DebuffTimerHandle = Handle;
		DebuffFinTimerHandle = FinHandle;
	}
	void SetDebuffTimerHandle(FTimerHandle& Handle) { DebuffTimerHandle = Handle; }
	void SetFinishTimerHandle(FTimerHandle& Handle) { DebuffFinTimerHandle = Handle; }

	FTimerHandle& GetDebuffTimerHandle() { return DebuffTimerHandle; }
	FTimerHandle& GetFinishTimerHandle() { return DebuffFinTimerHandle; }
	
	const bool& IsActive() { return bDebuffActive; }
	void SetActive(const bool Value) { bDebuffActive = Value; }

private:
	EUnitState Debuff;
	FTimerHandle DebuffTimerHandle;
	FTimerHandle DebuffFinTimerHandle;

	bool bDebuffActive = false;
};

USTRUCT(BlueprintType)
struct FDebuffInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FDebuffInfo() {}
	/**
	* @param	Loop : When true, the values of parameter Time and parameter Interval must be the same.
	*/
	FDebuffInfo(const float Value, const float Time, const float Interval, const bool Loop, EUnitState Type)
		: Value(Value), Time(Time), Interval(Interval), bLoop(Loop), DebuffType(Type) {}

public:
	float Value = 0.0f;
	float Time = 0.0f;
	float Interval = 0.0f;
	bool bLoop = false;

	EUnitState DebuffType;
};

UCLASS()
class FIVECIRCLEMAGE_API UC_DebuffInfo : public UObject
{
	GENERATED_BODY()
	
};
