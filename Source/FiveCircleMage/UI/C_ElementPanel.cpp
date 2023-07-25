// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_ElementPanel.h"
#include "Components/Image.h"
#include "GameFramework/PlayerController.h"

#include "Characters/Player/C_Mage.h"

#include "Utilities/CLog.h"

UC_ElementPanel::UC_ElementPanel(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UC_ElementPanel::SetOwner(AC_Mage* Unit)
{
	if (Unit == nullptr) return;

	this->Owner = Unit;
}

void UC_ElementPanel::ShowPanel()
{
	this->SetVisibility(ESlateVisibility::Visible);
	bIsActive = true;

	SelectedElement = ECastingElement::None;
}

//void UC_ElementPanel::HidePanel()
//{
//	this->SetVisibility(ESlateVisibility::Hidden);
//	bIsActive = false;
//
//	SelectedElement = ECastingElement::None;
//}
//
//void UC_ElementPanel::HidePanel(OUT ECastingElement& Element)
//{
//	this->SetVisibility(ESlateVisibility::Hidden);
//	bIsActive = false;
//
//	Element = SelectedElement;
//}

ECastingElement UC_ElementPanel::HidePanel()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	bIsActive = false;

	return SelectedElement;
}

void UC_ElementPanel::SetWindowSize(FVector2D WindowSize)
{
	WindowCenterPoint = WindowSize * 0.5f;
}

void UC_ElementPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UC_ElementPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UC_ElementPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

void UC_ElementPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) == true)
	{
		HidePanel();
		return;
	}

	if (bIsActive == false) return;

	Super::NativeTick(MyGeometry, InDeltaTime);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePos.X, MousePos.Y);

	SelectElement();
}

void UC_ElementPanel::SelectElement()
{
	bool bIsLeft = MousePos.X < WindowCenterPoint.X;
	bool bIsUp = MousePos.Y < WindowCenterPoint.Y;

	// Set Oringin Color
	FireElement->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
	IceElement->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
	LightElement->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
	DarkElement->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));

	if (bIsLeft)
	{
		if (bIsUp)
		{
			SelectedElement = ECastingElement::Fire;
			FireElement->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f));
		}
		else
		{
			SelectedElement = ECastingElement::Light;
			LightElement->SetColorAndOpacity(FLinearColor(0.0f, 0.7f, 0.0f));
		}
	}
	else
	{
		if (bIsUp)
		{
			SelectedElement = ECastingElement::Ice;
			IceElement->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 1.0f));
		}
		else
		{
			SelectedElement = ECastingElement::Dark;
			DarkElement->SetColorAndOpacity(FLinearColor(1.0f, 0.08f, 0.91f));
		}
	}
}