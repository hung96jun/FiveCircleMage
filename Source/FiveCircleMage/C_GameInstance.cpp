#include "C_GameInstance.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "AIController.h"

#include "Managers/C_MagicManager.h"
#include "Managers/C_WeaponManager.h"
#include "Managers/C_MonsterManager.h"
#include "Characters/Player/C_Mage.h"
#include "Characters/Player/C_PlayerController.h"

#include "Utilities/CLog.h"

UC_GameInstance::UC_GameInstance()
{
}

void UC_GameInstance::Init()
{
	Super::Init();

	if (MonsterSpawnDataTable != nullptr)
	{
		TArray<FMonsterPoolingInfo*> infos;
		MonsterSpawnDataTable->GetAllRows(FString(), infos);

		if (infos.IsEmpty() == true) return;

		for (FMonsterPoolingInfo* info : infos)
		{
			TArray<FMonsterPoolingInfo> addInfo;
			if (MonsterSpawnInfos.Contains(info->GetTriggerName()) == true)
				addInfo = MonsterSpawnInfos[info->GetTriggerName()];

			TPair<FString, TArray<FMonsterPoolingInfo>> pair;
			pair.Key = info->GetTriggerName();
			addInfo.Add(*info);
			pair.Value = addInfo;
			
			MonsterSpawnInfos.Add(pair);
		}
	}

	{
		for (TPair<FString, ULevelSequence*> pair : Cinematics)
		{
			TPair<FString, ALevelSequenceActor*> sequencePair;
			sequencePair.Key = pair.Key;
			//FMovieSceneSequencePlaybackSettings setting = FMovieSceneSequencePlaybackSettings();
			ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), pair.Value, FMovieSceneSequencePlaybackSettings(), sequencePair.Value);

			LevelSequences.Add(sequencePair);
		}
	}
}

void UC_GameInstance::GamePooling()
{
	// Init MagicManager
	{
		MagicManager = GetWorld()->SpawnActor<AC_MagicManager>();
		if (MagicManager == nullptr)
			CLog::Print(L"MagicManager is null", 100.0f, FColor::Red);

		MagicManager->Init();
	}

	// Init WeaponManager
	{
		WeaponManager = GetWorld()->SpawnActor<AC_WeaponManager>();
		if (WeaponManager == nullptr)
			CLog::Print(L"WeaponManager is null", 100.0f, FColor::Red);
	
		TArray<FWeaponSpawnInfo*> table;
		WeaponDataTable->GetAllRows(FString(), table);

		for (FWeaponSpawnInfo* info : table)
		{
			WeaponManager->SpawnWeapons(info->GetName(), info->GetClass(), info->GetMax(), info->GetDamage(), info->GetDamageFactor(), info->GetDebuffType());
		}
	}

	// Init MonsterManager
	{
		MonsterManager = GetWorld()->SpawnActor<AC_MonsterManager>();
		if(MonsterManager == nullptr)
			CLog::Print(L"MonsterManager is null", 100.0f, FColor::Red);

		MonsterManager->Init(MonsterInfoDataTable);
	}
}

void UC_GameInstance::TestSpawnMonster(FString Name, FVector Location)
{
	MonsterManager->SpawningMonster(Name, Location);
}

void UC_GameInstance::OnTrigger(const FString TriggerName)
{
	if (MonsterSpawnInfos.IsEmpty() == true) return;
	if (MonsterSpawnInfos.Contains(TriggerName) == false) return;

	TArray<FMonsterPoolingInfo> infos = MonsterSpawnInfos[TriggerName];
	for (FMonsterPoolingInfo info : infos)
	{
		if (info.GetName() == L"Boss")
		{
			CinemaPlay(L"BossSpawn");
			PlayerController->OpenBossUI(MonsterManager->SpawningBoss(info.GetName(), info.GetLocations()[0], info.GetRotations()[0]));
		}
		else
			MonsterManager->SpawningMonsters(info.GetName(), info.GetLocations(), info.GetRotations());
	}
}

void UC_GameInstance::SetGameInstance(AC_PlayerController* Controller)
{
	PlayerController = Controller;
}

const bool UC_GameInstance::CinemaPlay(FString Key)
{
	if (LevelSequences.Contains(Key) == false)
	{
		CLog::Print(L"GameInstance CinemaPlay function - LevelSequence nullptr (" + Key + ")", 100.0f, FColor::Red);
		return false;
	}

	LevelSequences.FindRef(Key)->SequencePlayer->Play();
	LevelSequences.FindRef(Key)->SequencePlayer->OnStop.AddDynamic(this, &UC_GameInstance::EndCinematic);
		
	CLog::Print(L"GameInstance CinemaPlay function - Play Success (" + Key + ")", 100.0f, FColor::Red);

	{
		Player = Cast<AC_Mage>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Player->SetActorHiddenInGame(true);
		PlayerController->UnPossess();
	}

	{
		AC_Unit* boss = Cast<AC_Unit>(MonsterManager->GetBoss());
		AAIController* controller = Cast<AAIController>(MonsterManager->GetBossController());

		if (boss != nullptr && controller != nullptr)
		{
			CLog::Print(L"CinemaPlay - boss and controller is nullptr", 100.0f, FColor::Red);

			boss->SetActorHiddenInGame(true);
			controller->UnPossess();
		}
	}

	return true;
}

void UC_GameInstance::EndCinematic()
{
	Player->SetActorHiddenInGame(false);
	PlayerController->Possess(Player);

	{
		AC_Unit* boss = Cast<AC_Unit>(MonsterManager->GetBoss());
		AAIController* controller = Cast<AAIController>(MonsterManager->GetBossController());

		if (boss != nullptr && controller != nullptr)
		{
			boss->SetActorHiddenInGame(false);
			controller->Possess(boss);
		}
	}
}
