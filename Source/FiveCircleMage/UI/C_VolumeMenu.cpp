// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_VolumeMenu.h"
#include "Components/Slider.h"
#include "Components/Button.h"

UC_VolumeMenu::UC_VolumeMenu(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
	FString path = L"";

	{
		path = L"Engine.SoundClass'/Game/Assets/Audio/SoundClasses/Master.Master'";
		ConstructorHelpers::FObjectFinder<USoundClass> master(*path);
		if (master.Succeeded())
		{
			SoundClass[0] = master.Object;
		}

		path = L"Engine.SoundClass'/Game/Assets/Audio/SoundClasses/BGM.BGM'";
		ConstructorHelpers::FObjectFinder<USoundClass> bgm(*path);
		if (bgm.Succeeded())
		{
			SoundClass[1] = bgm.Object;
		}

		path = L"Engine.SoundClass'/Game/Assets/Audio/SoundClasses/FX.FX'";
		ConstructorHelpers::FObjectFinder<USoundClass> fx(*path);
		if (fx.Succeeded())
		{
			SoundClass[2] = fx.Object;
		}

		path = L"Engine.SoundClass'/Game/Assets/Audio/SoundClasses/Voice.Voice'";
		ConstructorHelpers::FObjectFinder<USoundClass> voice(*path);
		if (voice.Succeeded())
		{
			SoundClass[3] = voice.Object;
		}
	}

	{
		path = L"Engine.SoundMix'/Game/Assets/Audio/SoundClasses/MasterMix.MasterMix'";
		ConstructorHelpers::FObjectFinder<USoundMix> master(*path);
		if (master.Succeeded())
		{
			SoundMix[0] = master.Object;
		}

		path = L"Engine.SoundMix'/Game/Assets/Audio/SoundClasses/BGMMix.BGMMix'";
		ConstructorHelpers::FObjectFinder<USoundMix> bgm(*path);
		if (bgm.Succeeded())
		{
			SoundMix[1] = bgm.Object;
		}

		path = L"Engine.SoundMix'/Game/Assets/Audio/SoundClasses/FXMix.FXMix'";
		ConstructorHelpers::FObjectFinder<USoundMix> fx(*path);
		if (fx.Succeeded())
		{
			SoundMix[2] = fx.Object;
		}

		path = L"Engine.SoundMix'/Game/Assets/Audio/SoundClasses/VoiceMix.VoiceMix'";
		ConstructorHelpers::FObjectFinder<USoundMix> voice(*path);
		if (voice.Succeeded())
		{
			SoundMix[3] = voice.Object;
		}
	}

}

void UC_VolumeMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Master->SetValue(50.0f);
	BGM->SetValue(50.0f);
	FXSound->SetValue(50.0f);
	VoiceSound->SetValue(50.0f);

	Master->OnValueChanged.AddDynamic(this, &UC_VolumeMenu::SetMasterVolume);
	BGM->OnValueChanged.AddDynamic(this, &UC_VolumeMenu::SetBGMVolume);
	FXSound->OnValueChanged.AddDynamic(this, &UC_VolumeMenu::SetFXSoundVolume);
	VoiceSound->OnValueChanged.AddDynamic(this, &UC_VolumeMenu::SetVoiceSoundVolume);

	if (SaveButton->OnClicked.IsBound() == true)
		SaveButton->OnClicked.Clear();
	SaveButton->OnClicked.AddDynamic(this, &UC_VolumeMenu::ClickedSaveButton);

	if (CancelButton->OnClicked.IsBound() == true)
		CancelButton->OnClicked.Clear();
	CancelButton->OnClicked.AddDynamic(this, &UC_VolumeMenu::ClickedCancelButton);
}

void UC_VolumeMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UC_VolumeMenu::OnOffMenu()
{
	bIsActive = true;

	SetVisibility(ESlateVisibility::Visible);
}

void UC_VolumeMenu::SetMasterVolume(float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix[0], SoundClass[0], Master->GetValue());

	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix[0]);
}

void UC_VolumeMenu::SetBGMVolume(float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix[1], SoundClass[1], BGM->GetValue());

	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix[1]);
}

void UC_VolumeMenu::SetFXSoundVolume(float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix[2], SoundClass[2], FXSound->GetValue());
}

void UC_VolumeMenu::SetVoiceSoundVolume(float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix[3], SoundClass[3], VoiceSound->GetValue());
}

void UC_VolumeMenu::ClickedSaveButton()
{
	bIsActive = false;

	SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UC_VolumeMenu::ClickedCancelButton()
{
	bIsActive = false;

	SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
