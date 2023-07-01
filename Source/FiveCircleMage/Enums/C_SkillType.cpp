#include "Enums/C_SkillType.h"
#include "Utilities/CLog.h"

FString UC_SkillType::EnumToString(const ESkillType Value)
{
	switch (Value)
	{
	case ESkillType::Missile: 
		return FString(L"Missile");
	case ESkillType::Beam: 
		return FString(L"Beam");
	case ESkillType::InPlace:
		return FString(L"InPlace");
	case ESkillType::Self:
		return FString(L"Self");
	}

	CLog::Print(L"SkillType Error", 1000.0f, FColor::Red);
	return FString("Error");
}

uint8 UC_SkillType::StringToInt(const FString Value)
{
	if (Value == L"Missile") 
		return 1;
	else if (Value == L"Beam") 
		return 2;
	else if (Value == L"InPlace") 
		return 3;
	else if (Value == L"Self") 
		return 4;

	return 0;
}
