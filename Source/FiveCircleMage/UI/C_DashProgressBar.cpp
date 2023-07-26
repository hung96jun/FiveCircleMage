#include "UI/C_DashProgressBar.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

#include "Utilities/CLog.h"

UC_DashProgressBar::UC_DashProgressBar(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
}

void UC_DashProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UC_DashProgressBar::NativeDestruct()
{
	Super::NativeDestruct();
}

void UC_DashProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (!bIsActive) return;

	Super::NativeTick(MyGeometry, InDeltaTime);

	DashValue += InDeltaTime;

	DashProgressBar->SetPercent(DashValue / DashCooltime);

	if (DashValue >= DashCooltime)
	{
		bIsActive = false;
		SetVisibility(ESlateVisibility::Hidden);
		StopAnimation(EnableDashAnim);

		DashValue = 0.0f;
	}
}

void UC_DashProgressBar::SetDashCoolTime(float CoolTime)
{
	DashCooltime = CoolTime;
}

void UC_DashProgressBar::CallDashProgressBar()
{
	if (bIsActive == true)
	{
		PlayAnimation(EnableDashAnim);
		return;
	}

	bIsActive = true;

	SetVisibility(ESlateVisibility::Visible);
}
