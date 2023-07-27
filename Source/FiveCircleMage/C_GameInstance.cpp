#include "C_GameInstance.h"

#include "Managers/C_MagicManager.h"
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
	CLog::Print(L"GameInstance Init", 50.0f, FColor::Cyan);
	MagicManager = GetWorld()->SpawnActor<AC_MagicManager>();
	if (MagicManager != nullptr)
		CLog::Print(L"MagicManager is not null", 50.0f, FColor::Red);
	else
		CLog::Print(L"MagicManager is null", 50.0f, FColor::Red);
	MagicManager->Init();
}
