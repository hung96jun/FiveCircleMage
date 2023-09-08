#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/C_WeaponSpawnInfo.h"
#include "Structs/C_MonsterSpawnInfo.h"
#include "C_GameInstance.generated.h"

/**
 * 
 */
class AC_MagicManager;
class AC_WeaponManager;
class AC_MonsterManager;
class AC_PlayerController;

UCLASS()
class FIVECIRCLEMAGE_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	TArray<FWeaponSpawnInfo> WeaponSpawnInfos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* WeaponDataTable;

	///**
	//* MonsterInfo
	//*/
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UDataTable* MonsterPoolDataTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* MonsterSpawnDataTable;

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

	void TestSpawnMonster(FString Name, FVector Location);

	/**
	* @param	TriggerName		TriggerBoxName
	*/
	void OnTrigger(const FString TriggerName);
	void SetGameInstance(AC_PlayerController* Controller);

protected:
	virtual void Init() override;

public:
	void GamePooling();

private:
	AC_MagicManager* MagicManager = nullptr;
	AC_WeaponManager* WeaponManager = nullptr;
	AC_MonsterManager* MonsterManager = nullptr;

	TMap<FString, TArray<FMonsterPoolingInfo>> MonsterSpawnInfos;

	AC_PlayerController* PlayerController = nullptr;
};
