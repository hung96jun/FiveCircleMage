#include "Managers/C_MagicManager.h"
#include "NiagaraSystem.h"

#include "Weapons/Magic/C_MagicSkill.h"
#include "Weapons/Magic/C_MagicMissile.h"
#include "Weapons/Magic/C_MagicCoord.h"
#include "Weapons/Magic/C_MagicInplace.h"
#include "Weapons/Magic/MesObjects/C_MagicMes.h"

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
					info.Key = pool->GetKey();
					info.Value = pool;

					PoolingInfos.Add(info);
				}
			}
		}

		{
			path = L"/Script/Engine.DataTable'/Game/Blueprint/DataTables/DT_MagicInfo.DT_MagicInfo'";
			ConstructorHelpers::FObjectFinder<UDataTable> table(*path);

			if (table.Succeeded())
			{
				MagicDataTable = table.Object;
				TArray<FMagicInfo*> magics;
				MagicDataTable->GetAllRows<FMagicInfo>(FString(), magics);
				for (FMagicInfo* magic : magics)
				{
					TPair<FString, FMagicInfo> info;
					info.Key = magic->GetMagicName();
					info.Value = magic;

					{
						path = magic->GetMainParticlePath();
						ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);
						if (niagara.Succeeded())
							info.Value.SetMainParticle(niagara.Object);
					}

					{
						path = magic->GetEndParticlePath();
						ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);
						if (niagara.Succeeded())
							info.Value.SetEndParticle(niagara.Object);
					}

					MagicInfos.Add(info);
				}
			}
		}
	}
}

void AC_MagicManager::BeginPlay()
{
	Super::BeginPlay();

	//////////////////////////////////////////////////////////////////////////////
	// Create Magic Objects
	//////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < CAST(int, ESkillType::Last); i++)
	{
		TPair<ESkillType, TArray<AC_MagicSkill*>> pair;
		TArray<AC_MagicSkill*> magics;
		for (int j = 0; j < MaxMagic; j++)
			magics.Add(GetWorld()->SpawnActor<AC_MagicSkill>());

		pair.Value = magics;
		Magics.Add(pair);
	}
	//////////////////////////////////////////////////////////////////////////////
}

void AC_MagicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AC_MagicSkill* AC_MagicManager::OnFireMagic(const FString Key, const ESkillType Type, const FVector Location)
{
	TArray<AC_MagicSkill*> magics = Magics.FindRef(Type);
	FMagicInfo info = MagicInfos.FindRef(Key);

	if (MagicCount[Type] >= MaxMagic)
		MagicCount[Type] = 0;

	AC_MagicSkill* magic = Cast<AC_MagicSkill>(magics[MagicCount[Type]]);
	magic->SetMagic(info.GetMainParticle(), info.GetEndParticle(), info.GetDamage(),
		info.GetMaxDuration(), info.GetDebuffType(), info.GetMoveSpeed());

	if (magic->IsActive() == true)
	{
		FString error = L"";
		error = L"Error : MagicManager class - OnFireMagic function, The corresponding MagicSkill object is already in use.";
		CLog::Print(error, 1000.0f, FColor::Red);
		return nullptr;
	}

	if (magic == nullptr)
	{
		FString error = L"";
		error = L"Error : MagicManager class - OnFireMagic function, magic value is nullptr";
		CLog::Print(error, 1000.0f, FColor::Red);
		return nullptr;
	}

	switch (info.GetMagicType())
	{
	case ESkillType::Missile:
	{
	}
	break;
	case ESkillType::Beam:
	{
	}
	break;
	case ESkillType::InPlace:
	{
		AC_MagicInplace* inplace = Cast<AC_MagicInplace>(magic);
		inplace->SetMaxRadius(info.GetTemp()[0]);
		inplace->SetSpreadSpeed(info.GetTemp()[1]);
	}
	break;
	case ESkillType::Coord:
	{
		Cast<AC_MagicCoord>(magic)->SetDelayTime(info.GetTemp()[0]);
	}
	break;
	case ESkillType::Self:
	{
	}
	break;
	}

	MagicCount[Type]++;

	return magic;
}
