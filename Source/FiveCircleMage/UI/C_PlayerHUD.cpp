#include "UI/C_PlayerHUD.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

#include "Utilities/CLog.h"

UC_PlayerHUD::UC_PlayerHUD(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

//void UC_PlayerHUD::NativeOnInitialized()
//{
//}
//
//void UC_PlayerHUD::NativePreConstruct()
//{
//}

void UC_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

}

void UC_PlayerHUD::NativeDestruct()
{
	Super::NativeDestruct();

}

void UC_PlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	HPPer = (*CurHealth) / (*MaxHealth);
	HP->SetPercent(HPPer);
}

void UC_PlayerHUD::SetHealth(float* Max, float* Cur)
{
	if (Max == nullptr || Cur == nullptr)
	{
		FString error = L"Error : PlayerHud Class - SetHeatlh parameter nullptr";
		CLog::Print(error, 1000.0f, FColor::Red);
		return;
	}

	MaxHealth = Max;
	CurHealth = Cur;
}
