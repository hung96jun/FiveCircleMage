#include "Managers/C_MonsterManager.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetStringLibrary.h"

#include "C_GameInstance.h"
#include "Managers/C_WeaponManager.h"
//#include "Characters/C_Unit.h"
#include "Characters/Monster/C_Monster.h"
#include "Characters/Monster/Boss/C_Boss.h"
#include "Characters/Monster/AIControllers/C_AIControllerBase.h"
#include "Characters/Monster/AIControllers/C_BossAIController.h"

AC_MonsterManager::AC_MonsterManager()
{
	FString path = L"/Script/Engine.Blueprint'/Game/Blueprint/Characters/Enemy/BpC_AIController.BpC_AIController_C'";
	ConstructorHelpers::FClassFinder<AC_AIControllerBase> controller(*path);
	if (controller.Succeeded())
		ControllerClass = controller.Class;
}

void AC_MonsterManager::BeginPlay()
{
	Super::BeginPlay();

}

void AC_MonsterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_MonsterManager::Init(UDataTable* Table)
{
	if (Table == nullptr) return;

	TArray<FMonsterInformation*> infos;
	Table->GetAllRows(FString(), infos);

	if (infos.IsEmpty() == true) return;

	for (FMonsterInformation* info : infos)
	{
		TPair<FString, FMonsterInformation> pair;
		pair.Key = info->GetName();
		pair.Value = (*info);

		MonsterInfos.Add(pair);
	}

	for (int i = 0; i < MaxSpawnCount; i++)
	{
		AC_Monster* monster = GetWorld()->SpawnActor<AC_Monster>();
		if (monster == nullptr) continue;

		monster->SetActorHiddenInGame(true);
		monster->SetActive(false);

		Monsters.Add(monster);

		AC_AIControllerBase* controller = GetWorld()->SpawnActor<AC_AIControllerBase>();
		if (controller == nullptr) continue;
		
		Controllers.Add(controller);
	}

	{
		BossMonster = GetWorld()->SpawnActor<AC_Boss>();
		if (BossMonster == nullptr) return;

		BossMonster->SetActorHiddenInGame(true);
		BossMonster->SetActive(false);

		BossController = GetWorld()->SpawnActor<AC_BossAIController>();
	}
}

AC_Monster* AC_MonsterManager::SpawningMonster(const FString Name, const FVector Location, const FRotator Rotation)
{
	if (Name == L"") return nullptr;
	if (MonsterInfos.Contains(Name) == false) return nullptr;

	AC_Monster* monster = nullptr;
	int originCount = CurCount;

	do
	{
		monster = Monsters[CurCount];
		if (monster != nullptr)
		{
			if (monster->IsActive() == true)
				monster = nullptr;
		}

		{
			CurCount++;
			if (CurCount >= MaxSpawnCount)
				CurCount = 0;
		}

		if (CurCount == originCount)
		{
			CLog::Print(L"Error : MonsterManager class - SpawningMonster function, 몬스터 전체 소환되어 있음", 1000.0f, FColor::Red);
			break;
		}

	} while (monster == nullptr);

	AC_AIControllerBase* controller = Controllers[CurCount];

	FMonsterInformation info = MonsterInfos[Name];

	monster->SetActorLocation(Location);
	monster->SetActorRotation(Rotation);
	monster->SetMonsterInfo(info);

	AttachWeapon(monster, info.GetWeaponInfos());

	monster->SetActive(true);
	controller->Possess(monster);
	
	return monster;
}

TArray<AC_Monster*> AC_MonsterManager::SpawningMonsters(const FString Name, const TArray<FVector> Locations, const TArray<FRotator> Rotations)
{
	if (Name == L"") return TArray<AC_Monster*>();
	if (MonsterInfos.Contains(Name) == false) return TArray<AC_Monster*>();

	TArray<AC_Monster*> monsters;
	FMonsterInformation info = MonsterInfos[Name];
		
	AC_Monster* monster = nullptr;
	int originCount = CurCount;

	for (int i = 0; i < Locations.Max(); i++)
	{
		do
		{
			monster = Monsters[CurCount];
			if (monster != nullptr)
			{
				if (monster->IsActive() == true)
					monster = nullptr;
			}

			{
				CurCount++;
				if (CurCount >= MaxSpawnCount)
					CurCount = 0;
			}

			if (CurCount == originCount)
			{
				CLog::Print(L"Error : MonsterManager class - SpawningMonsters function, 몬스터 전체 소환되어 있음", 1000.0f, FColor::Red);
				break;
			}

			if (monster != nullptr)
			{
				monster->SetActorLocation(Locations[i]);
				monster->SetActorRotation(Rotations[i]);
				monster->SetMonsterInfo(info);
				
				monster->SetActive(true);

				AttachWeapon(monster, info.GetWeaponInfos());

				monsters.Add(monster);

				AC_AIControllerBase* controller = Controllers[CurCount];
				controller->Possess(monster);
			}
		} while (monster == nullptr);
	}

	return monsters;
}

AC_Boss* AC_MonsterManager::SpawningBoss(const FString Name, const FVector Location, const FRotator Rotation)
{
	if (BossMonster == nullptr) return nullptr;
	if (BossController == nullptr) return nullptr;

	BossMonster->Spawn(Location);
	BossMonster->SetActorRotation(Rotation);

	BossController->Possess(BossMonster);

	return BossMonster;
}

void AC_MonsterManager::AttachWeapon(AC_Monster* Monster, const TArray<FAttachWeaponInfo> Infos)
{
	if (GetWorld()->GetGameInstance() != nullptr)
	{
		AC_WeaponManager* weaponManager = Cast<UC_GameInstance>(GetWorld()->GetGameInstance())->GetWeaponManager();
		if (weaponManager != nullptr)
		{
			for (FAttachWeaponInfo weaponInfo : Infos)
			{
				AC_WeaponBase* weapon = Cast<AC_WeaponBase>(weaponManager->ActiveWeapon(weaponInfo.GetName()));
				if (weapon == nullptr)
				{
					CLog::Print(L"Error : MonsterManager class - SpawningMonster function - weapon value is nullptr(" + weaponInfo.GetName() + ")", 1000.0f, FColor::Red);
					continue;
				}
				Monster->AttachWeapon(weapon, weaponInfo.GetBoneName(), weaponInfo.GetBoxCollisionExtent(), weaponInfo.GetWeaponOffset());
			}
		}
	}
}
