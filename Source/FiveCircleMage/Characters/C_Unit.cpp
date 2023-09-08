#include "Characters/C_Unit.h"

AC_Unit::AC_Unit()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(L"Character");
}

void AC_Unit::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = UnitStatus.GetCurMoveSpeed();
	
	//FString temp = L"";
	//temp = GetActorLabel();
	//temp += L"\nMaxHP : " + FString::SanitizeFloat(*UnitStatus.GetOriginHP());
	//temp += L"\nCurHP : " + FString::SanitizeFloat(*UnitStatus.GetCurHP());
	//
	//CLog::Print(temp, 10.0f, FColor::Purple);
}

void AC_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Unit::GetDmg(const float Dmg, const EUnitState Type)
{
	UnitStatus.GetDmg(Dmg);

	if ((*UnitStatus.GetCurHP()) <= 0.0f)
		OnDeath();
}

void AC_Unit::SetDebuffHandle(const int Index, FTimerDelegate& Delegate, const FDebuffInfo Info)
{
	ClearDebuffTimerHandle(Index);

	FTimerHandle debuffHandle;
	GetWorld()->GetTimerManager().SetTimer(debuffHandle, Delegate, Info.Interval, Info.bLoop);
	DebuffHandle[Index].SetDebuffTimerHandle(debuffHandle);

	FTimerHandle timerHandle;
	FTimerDelegate timerDel;
	timerDel.BindUFunction(this, "ClearDebuffTimerHandle", Index);

	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDel, Info.Time, false);
	DebuffHandle[Index].SetFinishTimerHandle(timerHandle);
	DebuffHandle[Index].SetActive(true);
}

void AC_Unit::ClearDebuffTimerHandle(const int Index)
{
	GetWorld()->GetTimerManager().ClearTimer(DebuffHandle[Index].GetDebuffTimerHandle());
	GetWorld()->GetTimerManager().ClearTimer(DebuffHandle[Index].GetFinishTimerHandle());

	DebuffHandle[Index].SetActive(false);

	CLog::Print(FString::FromInt(Index) + L"_Debuff Clear", 3.0f, FColor::Yellow);
}

void AC_Unit::DecreaseMoveSpeed(float Percent)
{
	UnitStatus.DecreaseMoveSpeed(Percent);
	GetCharacterMovement()->MaxWalkSpeed = UnitStatus.GetCurMoveSpeed();
}

void AC_Unit::ResetMoveSpeed()
{
	UnitStatus.ResetMoveSpeed();
	GetCharacterMovement()->MaxWalkSpeed = UnitStatus.GetOriginMoveSpeed();
}

const bool AC_Unit::IsFalling() const
{
	return GetCharacterMovement()->IsFalling();
}

void AC_Unit::SetActive(const bool Value)
{
	bActive = Value;

	if (bActive == true)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SetActorHiddenInGame(false);
	}

	else
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetActorHiddenInGame(true);
	}

	GetCharacterMovement()->MaxWalkSpeed = UnitStatus.GetCurMoveSpeed();
}
