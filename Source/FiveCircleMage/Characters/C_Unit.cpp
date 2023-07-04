#include "Characters/C_Unit.h"

AC_Unit::AC_Unit()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_Unit::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = UnitStatus.GetCurMoveSpeed();
}

void AC_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Unit::GetDmg(const float Dmg, const EUnitState Type)
{
	
}

void AC_Unit::SetDebuffHandle(const int Index, FTimerHandle& Handle, const float Time)
{
	/*if (DebuffHandle[Index].IsActive() == true)
		ClearDebuffTimerHandle(Index, true);

	DebuffHandle[Index].SetDebuffTimerHandle(Handle);

	FTimerHandle timerHandle;
	FTimerDelegate timerDel;
	timerDel.BindUFunction(this, "ClearDebuffTimerHandle", Index, false);

	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDel, Time, false);
	DebuffHandle[Index].SetActive(true);*/
}

void AC_Unit::SetDebuffHandle(const int Index, FTimerDelegate& Delegate, const FDebuffInfo Info)
{
	ClearDebuffTimerHandle(Index);

	FTimerHandle debuffHandle;
	GetWorld()->GetTimerManager().SetTimer(debuffHandle, Delegate, Info.Interval, true);
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
