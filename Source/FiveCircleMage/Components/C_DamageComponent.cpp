#include "Components/C_DamageComponent.h"
#include "Characters/C_Unit.h"

#include "Utilities/Defines.h"

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

void UC_DamageComponent::SetDebuff(AC_Unit* Target, const FDebuffInfo Information)
{
	FTimerDelegate timerDelegate;
	FTimerHandle handle;

	switch (Information.DebuffType)
	{
	case EUnitState::Normal:
		break;
	case EUnitState::Slow:
	{
		// ���ο�
		GiveSlow(Target, Information, true);
		// �ð������� ����
		timerDelegate.BindUFunction(this, "GiveSlow", Target, Information, false);
	}
	break;
	case EUnitState::Burn:
	{
		GiveBurn(Target, Information);
		timerDelegate.BindUFunction(this, "GiveBurn", Target, Information);
	}
	break;
	case EUnitState::Stun:
	{
		// ����
		GiveStun(Target, Information, true);
		// �ð������� ����
		timerDelegate.BindUFunction(this, "Stun", Target, Information, false);
	}
	break;
	}

	Target->SetDebuffHandle(CAST(int, Information.DebuffType), timerDelegate, Information);
}

void UC_DamageComponent::GiveBurn(AC_Unit* Target, const FDebuffInfo Information)
{
	Target->GetDmg(Information.Value, Information.DebuffType);

	CLog::Print(Target->GetName() + L" Burn", 10.0f, FColor::Red);
}

void UC_DamageComponent::GiveSlow(AC_Unit* Target, const FDebuffInfo Information, const bool bDecrease)
{
	if (bDecrease == true)
	{
		//Target->SetUnitState(Information.DebuffType);
		//Target->DecreaseMoveSpeed(Information.Value);

		CLog::Print(L"Decrease speed", 10.0f, FColor::Red);
	}

	else
	{
		//Target->SetUnitState(EUnitState::None);
		//Target->ResetMoveSpeed();

		CLog::Print(L"Reset speed", 10.0f, FColor::Red);
	}
}

void UC_DamageComponent::GiveStun(AC_Unit* Target, const FDebuffInfo Information, const bool bStun)
{
	if (bStun == false)
	{
		CLog::Print(L"OnPossess", 10.0f, FColor::Red);
		//Target->SetUnitState(Information.DebuffType);
	}

	else
	{
		CLog::Print(L"UnPossess", 10.0f, FColor::Red);
	}
}