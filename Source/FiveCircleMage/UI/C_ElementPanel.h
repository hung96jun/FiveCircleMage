// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/C_CastingElement.h"
#include "C_ElementPanel.generated.h"

/**
 * 
 */

class UImage;
class AC_Mage;

UCLASS()
class FIVECIRCLEMAGE_API UC_ElementPanel : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* FireElement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* IceElement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* LightElement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UImage* DarkElement;

public:
	UC_ElementPanel(const FObjectInitializer& ObjectInitializer);

	void SetOwner(AC_Mage* Unit);

	void ShowPanel();
	void HidePanel();
	void HidePanel(OUT ECastingElement& Element);

	void SetWindowSize(FVector2D WindowSize);

	const bool& IsActive() { return bIsActive; }

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void SelectElement();

private:
	AC_Mage* Owner = nullptr;

	FVector2D MousePos;
	FVector2D WindowCenterPoint;
	ECastingElement SelectedElement = ECastingElement::None;
	
	bool bIsActive = true;
};
