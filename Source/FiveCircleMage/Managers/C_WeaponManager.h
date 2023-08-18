#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_WeaponManager.generated.h"

class AC_WeaponBase;

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

	void SpawnWeapons(FString Name, TSubclassOf<AActor> Class, int Max);

	AC_WeaponBase* OnActive(const FString Name);
	const bool FindWeapon(const FString Name);

private:
	//TMap<FString, TArray<AC_WeaponBase*>> Weapons;
	TMap<FString, TArray<AC_WeaponBase*>> Weapons;
	TMap<FString, int> WeaponPoolMax;
	TMap<FString, int> WeaponPoolCount;
};
