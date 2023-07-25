#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/C_DebuffInfo.h"
#include "Enums/C_UnitType.h"
#include "C_DamageComponent.generated.h"


class AC_Unit;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIVECIRCLEMAGE_API UC_DamageComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UFUNCTION()
		void GiveBurn(AC_Unit* Target, const FDebuffInfo Information);

	UFUNCTION()
		void GiveSlow(AC_Unit* Target, const FDebuffInfo Information, const bool bDecrease);

	UFUNCTION()
		void GiveStun(AC_Unit* Target, const FDebuffInfo Information, const bool bStun);

public:	
	UC_DamageComponent();

	void GiveDmg(AActor* Target, const float Dmg, const EUnitState Type = EUnitState::Normal);
	void GiveHeal(AActor* Target, const float Amount);
	void SetTeamID(int ID) { TeamID = ID; }

protected:
	virtual void BeginPlay() override;

//private:
public:
	void SetDebuff(AC_Unit* Target, const FDebuffInfo Information);

private:
	int TeamID = -1;
};
