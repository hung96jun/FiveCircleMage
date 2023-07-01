#include "Components/C_DamageComponent.h"
#include "Characters/C_Unit.h"

UC_DamageComponent::UC_DamageComponent()
{

}

void UC_DamageComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UC_DamageComponent::GiveDmg(AActor* Target, const float Dmg, const EUnitState Type)
{
	if (Target == nullptr) return;

	AC_Unit* unitTarget = Cast<AC_Unit>(Target);
	if (unitTarget != nullptr && unitTarget->GetGenericTeamId() != TeamID)
	{
		unitTarget->GetDmg(Dmg, Type);
	}
}
