#include "FiveCircleMageGameModeBase.h"
#include "C_GameInstance.h"

AFiveCircleMageGameModeBase::AFiveCircleMageGameModeBase()
{

}

void AFiveCircleMageGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AFiveCircleMageGameModeBase::StartPlay()
{
	Super::StartPlay();

	GameInstance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	GameInstance->GamePooling();
}
