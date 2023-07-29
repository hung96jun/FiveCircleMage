// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FiveCircleMageGameModeBase.generated.h"

/**
 * 
 */
class UC_GameInstance;

UCLASS()
class FIVECIRCLEMAGE_API AFiveCircleMageGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFiveCircleMageGameModeBase();

public:
	virtual void BeginPlay() override;
	virtual void StartPlay() override;

private:
	UC_GameInstance* GameInstance = nullptr;
};
