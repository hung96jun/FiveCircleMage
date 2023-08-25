#include "C_GameInstance.h"

#include "Managers/C_MagicManager.h"
#include "Managers/C_WeaponManager.h"

#include "Utilities/CLog.h"

UC_GameInstance::UC_GameInstance()
{
}

AC_WeaponManager* UC_GameInstance::GetWeaponManager()
{
	if (WeaponManager == nullptr)
		CLog::Print(L"WeaponManger is nullptr from GameInstance class", 1000.0f, FColor::Red);
	else
		CLog::Print(L"WeaponManger is not nullptr from GameInstance class", 1000.0f, FColor::Blue);
	return WeaponManager;
}

void UC_GameInstance::Init()
{
	Super::Init();

}

void UC_GameInstance::GamePooling()
{
	CLog::Print(L"GameInstance Init", 50.0f, FColor::Cyan);

	// Init MagicManager
	{
		MagicManager = GetWorld()->SpawnActor<AC_MagicManager>();
		if (MagicManager != nullptr)
			CLog::Print(L"MagicManager is not null", 50.0f, FColor::Red);
		else
			CLog::Print(L"MagicManager is null", 50.0f, FColor::Red);

		MagicManager->Init();
	}

	//// Init WeaponManager
	//{
	//	WeaponManager = GetWorld()->SpawnActor<AC_WeaponManager>();
	//	if (WeaponManager != nullptr)
	//		CLog::Print(L"WeaponManager is not null", 50.0f, FColor::Red);
	//	else
	//		CLog::Print(L"WeaponManager is null", 50.0f, FColor::Red);
	//
	//	for (FWeaponSpawnInfo info : WeaponSpawnInfos)
	//	{
	//		WeaponManager->SpawnWeapons(info.GetName(), info.GetClass(), info.GetMax());
	//	}
	//}
}
