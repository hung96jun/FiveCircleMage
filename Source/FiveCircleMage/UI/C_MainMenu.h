// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_MainMenu.generated.h"

/**
 * 
 */
class UButton;
class AC_PlayerController;
class UC_OptionMenu;
class UC_VolumeMenu;

UCLASS()
class FIVECIRCLEMAGE_API UC_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* ResumeButton;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* GrafficOptionButton;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* SoundOptionButton;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* ExitButton;

public:
	UC_MainMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetOptionMenu(UC_OptionMenu* optionMenu) { OptionMenu = optionMenu; }

	void SetOptionMenu(UC_VolumeMenu* optionMenu) { VolumeMenu = optionMenu; }

	UFUNCTION()
	void OnOffMenu();
	
	UFUNCTION()
	void ClickedGrafficOptionButton();

	UFUNCTION()
	void ClickedSoundOptionButton();

	UFUNCTION()
	void ClickedExitButton();

private:
	bool bIsActive = false;

	UC_OptionMenu* OptionMenu = nullptr;
	UC_VolumeMenu* VolumeMenu = nullptr;
};
