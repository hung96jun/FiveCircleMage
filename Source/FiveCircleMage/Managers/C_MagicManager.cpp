#include "Managers/C_MagicManager.h"
#include "Sound/SoundBase.h"
#include "NiagaraSystem.h"

#include "Characters/C_Unit.h"

#include "Weapons/Magic/C_MagicSkill.h"
#include "Weapons/Magic/C_MagicMissile.h"
#include "Weapons/Magic/C_MagicCoord.h"
#include "Weapons/Magic/C_MagicInplace.h"
#include "Weapons/Magic/MesObjects/C_MagicMes.h"
#include "Weapons/Magic/MesObjects/C_SanctuaryArea.h"

#include "Utilities/CLog.h"
#include "Utilities/Defines.h"


AC_MagicManager::AC_MagicManager()
{
	PrimaryActorTick.bCanEverTick = false;

	FString path = L"";

	{
		{
			path = L"/Script/Engine.DataTable'/Game/Blueprint/DataTables/DT_MagicPoolingInfo.DT_MagicPoolingInfo'";
			ConstructorHelpers::FObjectFinder<UDataTable> table(*path);

			if (table.Succeeded())
			{
				PoolingDataTable = table.Object;
				TArray<FMagicPoolingInfo*> pooling;
				PoolingDataTable->GetAllRows<FMagicPoolingInfo>(FString(), pooling);
				for (FMagicPoolingInfo* pool : pooling)
				{
					TPair<FString, FMagicPoolingInfo> info;
					info.Key = pool->GetCode();
					info.Value = pool;

					PoolingInfos.Add(info);
				}
			}
		}

		{
			//path = L"/Script/Engine.DataTable'/Game/Blueprint/DataTables/DT_MagicInfo.DT_MagicInfo'";
			path = L"/Script/Engine.DataTable'/Game/Blueprint/DataTables/DT_MagicInfo2.DT_MagicInfo2'";
			ConstructorHelpers::FObjectFinder<UDataTable> table(*path);

			if (table.Succeeded())
			{
				MagicDataTable = table.Object;
				TArray<FMagicInfo*> magics;
				MagicDataTable->GetAllRows<FMagicInfo>(FString(), magics);
				for (FMagicInfo* magic : magics)
				{
					TPair<FString, FMagicInfo> info;
					info.Key = magic->GetMagicCode();
					info.Value = magic;

					{
						path = magic->GetMainParticlePath();
						if (path != L"")
						{
							ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);
							if (niagara.Succeeded())
								info.Value.SetMainParticle(niagara.Object);
							else
							{
								FString error = L"Niagara Failed : " + path;
								Errors.Add(error);
							}
						}
					}

					{
						path = magic->GetEndParticlePath();
						if (path != L"")
						{
							ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);
							if (niagara.Succeeded())
								info.Value.SetEndParticle(niagara.Object);
							else
							{
								FString error = L"Niagara Failed : " + path;
								Errors.Add(error);
							}
						}
					}

					MagicInfos.Add(info);
				}
			}
		}

		{
			path = "/Script/Engine.DataTable'/Game/Blueprint/DataTables/DT_MagicSoundInfo.DT_MagicSoundInfo'";

			ConstructorHelpers::FObjectFinder<UDataTable> table(*path);
			if (table.Succeeded())
			{
				MagicSoundDataTable = table.Object;

				TArray<FMagicSoundInfo*> soundInfos;
				MagicSoundDataTable->GetAllRows<FMagicSoundInfo>(FString(), soundInfos);
				for (FMagicSoundInfo* soundInfo : soundInfos)
				{
					TPair<FString, USoundBase*> info;
					info.Key = soundInfo->CodeNum;
					info.Value = soundInfo->MagicSound;

					MagicSounds.Add(info);
				}
			}
		}
	}
}

void AC_MagicManager::BeginPlay()
{
	Super::BeginPlay();

	//for (FString error : Errors)
	//{
	//	CLog::Print(error, 10.0f, FColor::Red);
	//}

	//CLog::Print(L"ErrorCount : " + FString::FromInt(Errors.Max()), 10.0f, FColor::Red);
}

void AC_MagicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_MagicManager::Init()
{
	//////////////////////////////////////////////////////////////////////////////
	// Create Magic Objects
	//////////////////////////////////////////////////////////////////////////////
	for (TPair<FString, FMagicPoolingInfo> info : PoolingInfos)
	{
		CreateMagicObject(info);

		TPair<FString, uint16> pair;
		pair.Key = info.Value.GetCode();
		pair.Value = 0;

		MagicCount.Add(pair);
	}
	//////////////////////////////////////////////////////////////////////////////
}

void AC_MagicManager::CreateMagicObject(TPair<FString, FMagicPoolingInfo> Info)
{
	TPair<FString, FMagicPool> pair;
	TArray<AC_MagicSkill*> magics;
	pair.Key = Info.Value.GetCode();

	FMagicInfo information = MagicInfos.FindRef(Info.Key);
	for (int i = 0; i < MaxMagic; i++)
	{
		AC_MagicSkill* magic = Cast<AC_MagicSkill>(GetWorld()->SpawnActor(Info.Value.GetClass()));
		magic->SetMagic(information.GetMainParticle(), information.GetMainLocation(), information.GetMainRotation(),
			information.GetEndParticle(), information.GetEndLocation(), information.GetEndRotation(),
			information.GetDamage(), information.GetMagicType(), information.GetMaxDuration(), 
			information.GetDebuffType(), information.GetMoveSpeed());
		magic->SetCollisionRadius(information.GetCollisionRadius());
		magic->SetCollisionHeight(information.GetCollisionHalfHeight());
		magic->SetOriginRotation(information.GetRotation());

		switch (magic->GetMagicType())
		{
		case ESkillType::Coord:
		{
			AC_MagicCoord* coord = Cast<AC_MagicCoord>(magic);
			coord->SetDelayTime(information.GetTemp()[0]);
		}
		break;
		case ESkillType::InPlace:
		{
			AC_MagicInplace* inplace = Cast<AC_MagicInplace>(magic);
			inplace->SetMaxRadius(information.GetTemp()[0]);
			inplace->SetSpreadSpeed(information.GetTemp()[1]);
		}
		break;
		case ESkillType::Mes:
		{
			AC_SanctuaryArea* santuary = Cast<AC_SanctuaryArea>(magic);
			if (santuary != nullptr)
			{
				santuary->SetLaunchPower(information.GetTemp()[0]);
			}
		}
			break;
		}

		magics.Add(magic);
	}
	pair.Value.Pool = magics;

	Magics.Add(pair);
}

AC_MagicSkill* AC_MagicManager::OnFireMagic(AC_Unit* OwnerActor, const FString Key, const FVector CasterLocation, const FVector TargetLocation, const FRotator Rotation)
{
	if (Magics.Contains(Key) == false) return nullptr;

	TArray<AC_MagicSkill*> magics = Magics.FindRef(Key).Pool;
	FMagicInfo info = MagicInfos.FindRef(Key);

	if (MagicCount[Key] >= MaxMagic)
		MagicCount[Key] = 0;

	AC_MagicSkill* magic = Cast<AC_MagicSkill>(magics[MagicCount[Key]]);	
	magic->SetOwnerActor(OwnerActor);

	if (magic == nullptr)
	{
		FString error = L"";
		error = L"Error : MagicManager class - OnFireMagic function, magic value is nullptr";
		CLog::Print(error, 1000.0f, FColor::Red);
		return nullptr;
	}

	magic->BeginCasting(CasterLocation, TargetLocation, Rotation);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), MagicSounds[Key], CasterLocation, Rotation, 0.5f);
	MagicCount[Key]++;

	return magic;
}
