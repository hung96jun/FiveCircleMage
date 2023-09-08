#include "Characters/Monster/Bear/C_Bear.h"

#include "Weapons/Weapon/C_WeaponBase.h"

#include "C_GameInstance.h"
#include "Managers/C_WeaponManager.h"
#include "Utilities/CLog.h"

AC_Bear::AC_Bear()
{
}

void AC_Bear::BeginPlay()
{
	Super::BeginPlay();

	// 몬스터 풀링 이전 테스트용 코드
	{
		//AC_WeaponBase* weapon = GetWorld()->SpawnActor<AC_WeaponBase>();
		//AttachWeapon(weapon, L"RightWeaponSocket");
		//weapon->SetActive(true);
		//weapon->SetActorHiddenInGame(false);
		//weapon->SetDamage(10.0f);

		UC_GameInstance* instance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance());
		if (instance == nullptr) return;
		
		AC_WeaponBase* weapon = Cast<AC_WeaponBase>(instance->GetWeaponManager()->ActiveWeapon(L"WeaponBase"));
		if (weapon == nullptr) return;
		
		AttachWeapon(weapon, L"RightWeaponSocket", FVector(50.0f, 50.0f, 50.0f));
	}
}

void AC_Bear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
