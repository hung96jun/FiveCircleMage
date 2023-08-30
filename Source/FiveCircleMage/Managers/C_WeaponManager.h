#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/C_UnitType.h"
#include "C_WeaponManager.generated.h"

//class AC_WeaponBase;
class AC_DamageBase;

UCLASS()
class FIVECIRCLEMAGE_API AC_WeaponManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_WeaponManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SpawnWeapons(const FString Name, TSubclassOf<AActor> Class, int Max);
	void SpawnWeapons(const FString Name, TSubclassOf<AActor> Class, const int Max, const float Damage, const float DamageFactor, const EUnitState DebuffType);

	AC_DamageBase* ActiveWeapon(const FString Name);
	const bool FindWeapon(const FString Name);

private:
	//TMap<FString, TArray<AC_WeaponBase*>> Weapons;
	TMap<FString, TArray<AC_DamageBase*>> Weapons;
	TMap<FString, int> WeaponPoolMax;
	TMap<FString, int> WeaponPoolCount;
};

