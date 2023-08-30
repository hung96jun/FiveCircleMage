#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/C_UnitType.h"
#include "C_MonsterManager.generated.h"

class AC_Unit;

UCLASS()
class FIVECIRCLEMAGE_API AC_MonsterManager : public AActor
{
	GENERATED_BODY()

protected:

	
public:
	AC_MonsterManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Init(UDataTable* DataTable);

	AC_DamageBase* SpawnningMonster(const FString Name);
	const bool FindMonster(const FString Name);

private:
	TMap<FString, TArray<AC_Unit*>> Monsters;
	TMap<FString, int> MonsterPoolMax;
	TMap<FString, int> MonsterPoolCount;
};

