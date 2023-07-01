#include "Enums/C_CastingElement.h"
#include "Utilities/CLog.h"

UC_CastingElement::UC_CastingElement()
{
}

FString UC_CastingElement::EnumToString(const ECastingElement Value)
{
	switch (Value)
	{
	case ECastingElement::Fire: 
		return FString(L"Fire");
		break;
	case ECastingElement::Ice: 
		return FString(L"Ice");
		break;
	case ECastingElement::Light: 
		return FString(L"Light");
		break;
	case ECastingElement::Dark: 
		return FString(L"Dark");
		break;
	default:
		break;
	}

	CLog::Print(L"CastingElement Error", 1000.0f, FColor::Red);
	return FString("Error");
}

uint8 UC_CastingElement::StringToInt(const FString Value)
{

	if (Value == L"Fire")
		return 1;
	else if (Value == L"Ice")
		return 2;
	else if (Value == L"Light")
		return 3;
	else if (Value == L"Dark")
		return 4;

	return 0;
}
