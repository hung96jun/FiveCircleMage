#include "Actors/C_SpawnTriggerBox.h"

#include "Characters/Player/C_Mage.h"
#include "C_GameInstance.h"
#include "Managers/C_MonsterManager.h"

#include "Utilities/CLog.h"

AC_SpawnTriggerBox::AC_SpawnTriggerBox()
{
}

void AC_SpawnTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_SpawnTriggerBox::OnBegin);
}

void AC_SpawnTriggerBox::OnBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (bActive == false) return;
	if (OtherActor == nullptr) return;

	AC_Mage* otherActor = Cast<AC_Mage>(OtherActor);
	if (otherActor == nullptr) return;

	UC_GameInstance* instance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
	if (instance == nullptr) return;

	instance->OnTrigger(Key);
	bActive = false;

	CLog::Print(L"OnTrigger", 10.0f, FColor::Cyan);
}
