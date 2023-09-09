#include "C_GameInstance.h"

#include "Managers/C_MagicManager.h"
#include "Managers/C_WeaponManager.h"
#include "Managers/C_MonsterManager.h"
#include "Characters/Player/C_PlayerController.h"

#include "Utilities/CLog.h"

UC_GameInstance::UC_GameInstance()
{
}

void UC_GameInstance::Init()
{
	Super::Init();

	if (MonsterSpawnDataTable != nullptr)
	{
		TArray<FMonsterPoolingInfo*> infos;
		MonsterSpawnDataTable->GetAllRows(FString(), infos);

		if (infos.IsEmpty() == true) return;

		for (FMonsterPoolingInfo* info : infos)
		{
			TArray<FMonsterPoolingInfo> addInfo;
			if (MonsterSpawnInfos.Contains(info->GetTriggerName()) == true)
				addInfo = MonsterSpawnInfos[info->GetTriggerName()];

			TPair<FString, TArray<FMonsterPoolingInfo>> pair;
			pair.Key = info->GetTriggerName();
			addInfo.Add(*info);
			pair.Value = addInfo;
			
			MonsterSpawnInfos.Add(pair);
		}
	}
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

		MonsterManager->Init(MonsterInfoDataTable);
	}
}

void UC_GameInstance::TestSpawnMonster(FString Name, FVector Location)
{
	MonsterManager->SpawningMonster(Name, Location);
}

void UC_GameInstance::OnTrigger(const FString TriggerName)
{
	if (MonsterSpawnInfos.IsEmpty() == true) return;
	if (MonsterSpawnInfos.Contains(TriggerName) == false) return;

	TArray<FMonsterPoolingInfo> infos = MonsterSpawnInfos[TriggerName];
	for (FMonsterPoolingInfo info : infos)
	{
		if (info.GetName() == L"Boss")
			PlayerController->OpenBossUI(MonsterManager->SpawningBoss(info.GetName(), info.GetLocations()[0], info.GetRotations()[0]));
		else
			MonsterManager->SpawningMonsters(info.GetName(), info.GetLocations(), info.GetRotations());
	}
}

void UC_GameInstance::SetGameInstance(AC_PlayerController* Controller)
{
	PlayerController = Controller;
}
