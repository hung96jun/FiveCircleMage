#pragma once

#include "CoreMinimal.h"

#define PrintLine(){CLog::Log(__FUNCTION__, __LINE__);}

class FIVECIRCLEMAGE_API CLog
{
public:
	static void Print(int32 InValue, float Duration = 10.0f, FColor InColor = FColor::Blue, int32 InKey = -1);
	static void Print(float InValue, float Duration = 10.0f, FColor InColor = FColor::Blue, int32 InKey = -1);
	static void Print(const FString& InValue, float Duration = 10.0f, FColor InColor = FColor::Blue, int32 InKey = -1);
	static void Print(const FVector& InValue, float Duration = 10.0f, FColor InColor = FColor::Blue, int32 InKey = -1);
	static void Print(const FRotator& InValue, float Duration = 10.0f, FColor InColor = FColor::Blue, int32 InKey = -1);

	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InObject);
	static void Log(const FString& InFuncName, int32 InLineNumber);
};