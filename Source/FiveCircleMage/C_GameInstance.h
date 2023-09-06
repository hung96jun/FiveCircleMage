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
class AC_MonsterManager;

UCLASS()
class FIVECIRCLEMAGE_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	TArray<FWeaponSpawnInfo> WeaponSpawnInfos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* WeaponDataTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* MonsterPoolDataTable;

	/**
	* 몬스터를 배치하는 곳에서 사용할 DataTable
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* MonsterInfoDataTable;

public:
	UC_GameInstance();

	AC_MagicManager* GetMagicManager() { return MagicManager; }
	AC_WeaponManager* GetWeaponManager() { return WeaponManager; }
	AC_MonsterManager* GetMonsterManager() { return MonsterManager; }

protected:
	virtual void Init() override;

public:
	void GamePooling();

private:
	AC_MagicManager* MagicManager = nullptr;
	AC_WeaponManager* WeaponManager = nullptr;
	AC_MonsterManager* MonsterManager = nullptr;
};
