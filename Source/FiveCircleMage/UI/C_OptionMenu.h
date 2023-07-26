// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_OptionMenu.generated.h"

/**
 * 
 */

class UGameUserSettings;
class UButton;
class UComboBoxString;

UCLASS()
class FIVECIRCLEMAGE_API UC_OptionMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UComboBoxString* AntiAliasing;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UComboBoxString* PostProcessing;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UComboBoxString* Shadows;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UComboBoxString* Textures;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UComboBoxString* Shading;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* SaveButton;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* CancelButton;

private:
	UFUNCTION()
	void SetAntiAliasingOption(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void SetPostProcessingOption(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void SetShadowsOption(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void SetTexturesOption(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void SetShadingOption(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void ClickedSaveButton();
	UFUNCTION()
	void ClickedCancelButton();

public:
	UC_OptionMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnOffMenu();
	bool IsActive() { return bIsActive; }

private:
	void AddOption(UComboBoxString* BoxName);

private:
	UGameUserSettings* GameUserSettings;

	bool bIsActive = false;
	bool bInitialize = false;

	int32 Index[5] = { 0, 0, 0, 0, 0 };
};
