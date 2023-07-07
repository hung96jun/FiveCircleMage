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
}

void UC_ElementPanel::HidePanel()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	bIsActive = false;

	SelectedElement = ECastingElement::None;
}

void UC_ElementPanel::HidePanel(OUT ECastingElement& Element)
{
	this->SetVisibility(ESlateVisibility::Hidden);
	bIsActive = false;

	Element = SelectedElement;
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
	if (bIsActive == false) return;

	Super::NativeTick(MyGeometry, InDeltaTime);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePos.X, MousePos.Y);

	SelectElement();
}

void UC_ElementPanel::SelectElement()
{
	bool bIsLeft = MousePos.X < WindowCenterPoint.X;
	bool bIsUp = MousePos.Y < WindowCenterPoint.Y;

	if (bIsLeft)
	{
		if (bIsUp)
		{
			//SelectedElement = ECastingElement::Fire;
			//FireElement->SetColorAndOpacity(FColor(0.5f, 0.7f, 0.0f));
			CLog::Print(FString("Fire"), 0.01f);
		}
		else
		{
			//SelectedElement = ECastingElement::Light;
			CLog::Print(FString("Light"), 0.01f);
		}
	}
	else
	{
		if (bIsUp)
		{
			//SelectedElement = ECastingElement::Ice;
			CLog::Print(FString("Ice"), 0.01f);
		}
		else
		{
			//SelectedElement = ECastingElement::Dark;
			CLog::Print(FString("Dark"), 0.01f);
		}
	}
}