// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_Direction.generated.h"


UENUM(BlueprintType)
enum class EDirectionState : uint8
{
	None,
	Forward,
	Forward_Left,
	Forward_Right,
	Back,
	Back_Left,
	Back_Right,
	Left,
	Right
};
/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_Direction : public UObject
{
	GENERATED_BODY()

public:
	UC_Direction();
};
