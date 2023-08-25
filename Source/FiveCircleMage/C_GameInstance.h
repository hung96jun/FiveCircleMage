#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/C_WeaponSpawnInfo.h"
#include "C_GameInstance.generated.h"

/**
 * 
 */
class AC_MagicManager;
class AC_WeaponManager;

UCLASS()
class FIVECIRCLEMAGE_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FWeaponSpawnInfo> WeaponSpawnInfos;

public:
	UC_GameInstance();

	AC_MagicManager* GetMagicManager() { return MagicManager; }
	AC_WeaponManager* GetWeaponManager();// { return WeaponManager; }

protected:
	virtual void Init() override;

public:
	void GamePooling();

private:
	AC_MagicManager* MagicManager = nullptr;
	AC_WeaponManager* WeaponManager = nullptr;
};
