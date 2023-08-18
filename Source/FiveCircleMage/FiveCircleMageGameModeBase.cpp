#include "FiveCircleMageGameModeBase.h"
#include "C_GameInstance.h"

#include "Utilities/CLog.h"

AFiveCircleMageGameModeBase::AFiveCircleMageGameModeBase()
{
	FString path = L"";

	//{
	//	path = L"/Script/Engine.Blueprint'/Game/Blueprint/BpC_GameInstance.BpC_GameInstance'";
	//	ConstructorHelpers::FObjectFinder<UC_GameInstance> instance(*path);
	//
	//	if (instance.Succeeded())
	//	{
	//		GameInstance = instance.Object;
	//	}
	//}
}

void AFiveCircleMageGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance == nullptr)
	{
		FString error = L"";
		error = L"Fatal Error : GameInstance class is nullptr";
		CLog::Print(error, 1000.0f, FColor::Red);

		return;
	}

	GameInstance->GamePooling();
}

void AFiveCircleMageGameModeBase::StartPlay()
{
	Super::StartPlay();


}
