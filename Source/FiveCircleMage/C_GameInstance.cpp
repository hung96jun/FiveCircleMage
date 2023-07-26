#include "C_GameInstance.h"

#include "Managers/C_MagicManager.h"

UC_GameInstance::UC_GameInstance()
{
}

void UC_GameInstance::Init()
{
	Super::Init();

	MagicManager = GetWorld()->SpawnActor<AC_MagicManager>();
}
