#include "C_GameInstance.h"

#include "Managers/C_MagicManager.h"
#include "Managers/C_WeaponManager.h"
#include "Managers/C_MonsterManager.h"

#include "Utilities/CLog.h"

UC_GameInstance::UC_GameInstance()
{
}

void UC_GameInstance::Init()
{
	Super::Init();

}

void UC_GameInstance::GamePooling()
{
	// Init MagicManager
	{
		MagicManager = GetWorld()->SpawnActor<AC_MagicManager>();
		if (MagicManager == nullptr)
			CLog::Print(L"MagicManager is null", 100.0f, FColor::Red);

		MagicManager->Init();
	}

	// Init WeaponManager
	{
		WeaponManager = GetWorld()->SpawnActor<AC_WeaponManager>();
		if (WeaponManager == nullptr)
			CLog::Print(L"WeaponManager is null", 100.0f, FColor::Red);
	
		TArray<FWeaponSpawnInfo*> table;
		WeaponDataTable->GetAllRows(FString(), table);

		for (FWeaponSpawnInfo* info : table)
		{
			WeaponManager->SpawnWeapons(info->GetName(), info->GetClass(), info->GetMax(), info->GetDamage(), info->GetDamageFactor(), info->GetDebuffType());
		}
	}

	// Init MonsterManager
	{
		MonsterManager = GetWorld()->SpawnActor<AC_MonsterManager>();
		if(MonsterManager == nullptr)
			CLog::Print(L"MonsterManager is null", 100.0f, FColor::Red);

		MonsterManager->Init(MonsterPoolDataTable);
	}
}
