#include "Enums/C_UnitType.h"
#include "Utilities/CLog.h"

UC_UnitType::UC_UnitType()
{
}

FString UC_UnitType::EnumToString(const EUnitForceType  Value)
{
	switch (Value)
	{
	case EUnitForceType::Player:
		return FString(L"Player");
		break;
	case EUnitForceType::Monster:
		return FString(L"Monster");
		break;
	}

	CLog::Print(L"UnitType Error", 1000.0f, FColor::Red);
	return FString("Error");
}

EUnitForceType UC_UnitType::StringToEnum(const FString Value)
{
	if (Value == L"Player")
		return EUnitForceType::Player;
	else if (Value == L"Monster")
		return EUnitForceType::Monster;

	return EUnitForceType::None;
}

uint8 UC_UnitType::StringToInt(const FString Value)
{
	if (Value == L"Player")
		return 1;
	else if (Value == L"Monster")
		return 2;

	return 0;
}

UC_UnitState::UC_UnitState()
{
}

FString UC_UnitState::EnumToString(const EUnitState Value)
{
	switch (Value)
	{
	case EUnitState::Normal:
		return FString(L"Normal");
		break;
	case EUnitState::Slow:
		return FString(L"Slow");
		break;
	case EUnitState::Burn:
		return FString(L"Burn");
		break;
	case EUnitState::Stun:
		return FString(L"Stun");
		break;
	}

	return FString(L"None");
}

EUnitState UC_UnitState::StringToEnum(const FString Value)
{
	if (Value == L"Slow")
		return EUnitState::Slow;
	else if (Value == L"Burn")
		return EUnitState::Burn;
	else if (Value == L"Stun")
		return EUnitState::Stun;

	return EUnitState::Normal;
}

uint8 UC_UnitState::StringToInt(const FString Value)
{
	if (Value == L"Slow")
		return 1;
	else if (Value == L"Burn")
		return 2;
	else if (Value == L"Stun")
		return 3;

	return 0;
}