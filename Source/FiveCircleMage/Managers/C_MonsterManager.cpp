#include "Managers/C_MonsterManager.h"

#include "Structs/C_MonsterSpawnInfo.h"
#include "Characters/C_Unit.h"

AC_MonsterManager::AC_MonsterManager()
{
}

void AC_MonsterManager::BeginPlay()
{
	Super::BeginPlay();

}

void AC_MonsterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_MonsterManager::Init(UDataTable* DataTable)
{
	if (DataTable == nullptr) return;


}

AC_DamageBase* AC_MonsterManager::SpawnningMonster(const FString Name)
{
	return nullptr;
}

const bool AC_MonsterManager::FindMonster(const FString Name)
{
	return false;
}
