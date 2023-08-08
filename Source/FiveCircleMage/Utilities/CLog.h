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

	static void DrawLine(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.0f, float Thickness = 5.0f);
	static void DrawCircle(const UWorld* InWorld, const FVector Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.0f, uint8 DepthPriority = 0, float Tickness = 0.0f);
	static void DrawCapsule(const UWorld* InWorld, FVector const& Center, float HalfHeight, float Radius, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.0f, uint8 DepthPriority = 0, float Tickness = 0.0f);
	static void DrawSphere(const UWorld* InWorld, FVector const& Center, float Radius, FColor const& Color, float LifeTime = -1.0f, int32 Segments = 40, bool bPersistentLines = false, uint8 DepthPriority = 0, float Tickness = 0.0f);
};