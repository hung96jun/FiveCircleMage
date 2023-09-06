#include "UI/C_MonsterUI.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

UC_MonsterUI::UC_MonsterUI(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UC_MonsterUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UC_MonsterUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void UC_MonsterUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UC_MonsterUI::Init()
{
	SetHealth(1.0f);
	SetVisibility(ESlateVisibility::Hidden);
}

void UC_MonsterUI::SetHealth(float Percent)
{
	FTimerDelegate timerDelegate;

	HP->SetPercent(Percent);
	SetVisibility(ESlateVisibility::Visible);
	SetRenderOpacity(1.0f);
	CurHiddenTime = OriginHiddenTime;

	timerDelegate.BindUFunction(this, "Hiding");

	ClearTimer();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, timerDelegate, 0.01f, true, 1.0f);
}

void UC_MonsterUI::Hiding()
{
	CurHiddenTime -= 0.02f;

	float opacity = CurHiddenTime / OriginHiddenTime;

	if (opacity > 0.0f)
		SetRenderOpacity(opacity);
	else
		SetOff();
}

void UC_MonsterUI::SetOff()
{
	SetVisibility(ESlateVisibility::Hidden);
	ClearTimer();
}

void UC_MonsterUI::ClearTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}