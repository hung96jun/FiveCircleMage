// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_VolumeMenu.generated.h"

/**
 * 
 */

class USound;
class USlider;
class UButton;

UCLASS()
class FIVECIRCLEMAGE_API UC_VolumeMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		USlider* Master;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		USlider* BGM;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		USlider* FXSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		USlider* VoiceSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* SaveButton;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		UButton* CancelButton;

private:
	UFUNCTION()
		void SetMasterVolume(float Value);
	UFUNCTION()
		void SetBGMVolume(float Value);
	UFUNCTION()
		void SetFXSoundVolume(float Value);
	UFUNCTION()
		void SetVoiceSoundVolume(float Value);
	UFUNCTION()
		void ClickedSaveButton();
	UFUNCTION()
		void ClickedCancelButton();


public:
	UC_VolumeMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnOffMenu();
	bool IsActive() { return bIsActive; }

private:
	void LoadSettings();



private:
	bool bIsActive = false;

	USoundClass* SoundClass[4];
	USoundMix* SoundMix[4];
};
