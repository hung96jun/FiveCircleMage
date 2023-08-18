#include "Managers/C_WeaponManager.h"

#include "Weapons/Weapon/C_WeaponBase.h"

AC_WeaponManager::AC_WeaponManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_WeaponManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_WeaponManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_WeaponManager::SpawnWeapons(FString Name, TSubclassOf<AActor> Class, int Max)
{
	//if (Class == nullptr) return;
	//if (Class.Get() == nullptr) return;
	if (Weapons.Contains(Name) == true) return;

	FString debug = L"";

	{
		TPair<FString, TArray<AC_WeaponBase*>> pair;
		pair.Key = Name;

		TArray<AC_WeaponBase*> weapons;

		int count = 0;

		for (int i = 0; i < Max; i++)
		{
			//AActor* actor = GetWorld()->SpawnActor<AActor>(Class, FVector(0.0f, 0.0f, -500.0f), FRotator::ZeroRotator);
			//AC_WeaponBase* weapon = Cast<AC_WeaponBase>(actor);
			AC_WeaponBase* weapon = GetWorld()->SpawnActor<AC_WeaponBase>(Class, FVector(0.0f, 0.0f, -500.0f), FRotator::ZeroRotator);
			if (weapon == nullptr) continue;
			//weapon->SetActive(false);
			weapons.Add(weapon);
			count++;
		}

		pair.Value = weapons;

		Weapons.Add(pair);
		
		debug = Name + L"_Weapon - " + FString::FromInt(count) + L" Spawn";
		CLog::Print(debug, 10.0f, FColor::Yellow);
	}

	{
		TPair<FString, int> pair;
		pair.Key = Name;
		pair.Value = Max;
		WeaponPoolMax.Add(pair);
	}

	{
		TPair<FString, int> pair;
		pair.Key = Name;
		pair.Value = 0;
		WeaponPoolCount.Add(pair);
	}
}

AC_WeaponBase* AC_WeaponManager::OnActive(const FString Name)
{
	AC_WeaponBase* weapon = nullptr;
	TArray<AC_WeaponBase*> weapons = Weapons[Name];
	int max = WeaponPoolMax[Name];
	int count = WeaponPoolCount[Name];
	count++;

	weapon = weapons[count];

	if (weapon->IsActive() == true)
	{
		for (int i = 0; i < max; i++)
		{
			if (weapons[i]->IsActive() == false)
			{
				weapon = weapons[i];
				WeaponPoolCount[Name] = i;
				break;
			}
		}
	}
	else
	{
		if (count >= max) 
			count = 0;

		WeaponPoolCount[Name] = count;
	}

	return weapon;
}

const bool AC_WeaponManager::FindWeapon(const FString Name)
{
	return Weapons.Contains(Name);
}
