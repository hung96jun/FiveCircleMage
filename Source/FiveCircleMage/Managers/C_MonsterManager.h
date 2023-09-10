#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/C_UnitType.h"
#include "Structs/C_MonsterSpawnInfo.h"
#include "Structs/C_MonsterSpawnInfo.h"
#include "C_MonsterManager.generated.h"

class UDataTable;

class AC_Unit;
class AC_Monster;
class AC_AIControllerBase;

class AC_Boss;
class AC_BossAIController;

UCLASS()
class FIVECIRCLEMAGE_API AC_MonsterManager : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AC_AIControllerBase> ControllerClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxSpawnCount = 15;
	
public:
	AC_MonsterManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/**
	* @param	Table		MonsterPoolingInfo DataTable
	*/
	void Init(UDataTable* Table);

	AC_Monster* SpawningMonster(const FString Name, const FVector Location, const FRotator Rotation = FRotator::ZeroRotator);
	TArray<AC_Monster*> SpawningMonsters(const FString Name, const TArray<FVector> Locations);

	AC_Boss* SpawningBoss(const FString Name, const FVector Location, const FRotator Rotation = FRotator::ZeroRotator);
		
	TArray<AC_Monster*> GetMonsters(FString Name);

	AC_Boss* GetBoss() { return BossMonster; }
	AC_BossAIController* GetBossController() { return BossController; }

private:
	void AttachWeapon(AC_Monster* Monster, const TArray<FAttachWeaponInfo> Infos);

private:
	TMap<FString, FMonsterInformation> MonsterInfos;

	TArray<AC_Monster*> Monsters;
	TArray<AC_AIControllerBase*> Controllers;

	AC_Boss* BossMonster;
	AC_BossAIController* BossController;

	int CurCount = 0;
};