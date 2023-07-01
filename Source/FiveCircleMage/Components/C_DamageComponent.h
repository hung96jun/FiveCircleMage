#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/C_UnitType.h"
#include "C_DamageComponent.generated.h"


class AC_Unit;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIVECIRCLEMAGE_API UC_DamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_DamageComponent();

	void GiveDmg(AActor* Target, const float Dmg, const EUnitState Type);
	void SetTeamID(int ID) { TeamID = ID; }
	void SetDamage(float Value) { Damage = Value; }

protected:
	virtual void BeginPlay() override;

private:
	int TeamID = -1;
	float Damage = 0.0f;
};
