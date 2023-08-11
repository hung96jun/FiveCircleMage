#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_GameInstance.generated.h"

/**
 * 
 */
class AC_MagicManager;

UCLASS()
class FIVECIRCLEMAGE_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AC_MagicManager* MagicManager = nullptr;

public:
	UC_GameInstance();

	AC_MagicManager* GetMagicManager() { return MagicManager; }

protected:
	virtual void Init() override;

public:
	void GamePooling();

};
