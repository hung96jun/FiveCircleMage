// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_OptionMenu.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Button.h"

#include "Characters/Player/C_Mage.h"

UC_OptionMenu::UC_OptionMenu(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
}

void UC_OptionMenu::NativeConstruct()
{
	if (bInitialize == true) return;

	Super::NativeConstruct();

	GameUserSettings = UGameUserSettings::GetGameUserSettings();

	ResolutionScale->AddOption("1024 x 768");
	ResolutionScale->AddOption("1366 x 768");
	ResolutionScale->AddOption("1920 x 1200");

	AddOption(AntiAliasing);
	AddOption(PostProcessing);
	AddOption(Shadows);
	AddOption(Textures);
	AddOption(Shading);

	ResolutionScale->OnSelectionChanged.AddDynamic(this, &UC_OptionMenu::SetResoultionScale);

	FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UC_OptionMenu::SetFullScreenMode);

	AntiAliasing->OnSelectionChanged.AddDynamic(this, &UC_OptionMenu::SetAntiAliasingOption);

	PostProcessing->OnSelectionChanged.AddDynamic(this, &UC_OptionMenu::SetPostProcessingOption);

	Shadows->OnSelectionChanged.AddDynamic(this, &UC_OptionMenu::SetShadowsOption);

	Textures->OnSelectionChanged.AddDynamic(this, &UC_OptionMenu::SetTexturesOption);

	Shading->OnSelectionChanged.AddDynamic(this, &UC_OptionMenu::SetShadingOption);

	if (SaveButton->OnClicked.IsBound() == true)
		SaveButton->OnClicked.Clear();
	SaveButton->OnClicked.AddDynamic(this, &UC_OptionMenu::ClickedSaveButton);

	if (CancelButton->OnClicked.IsBound() == true)
		CancelButton->OnClicked.Clear();
	CancelButton->OnClicked.AddDynamic(this, &UC_OptionMenu::ClickedCancelButton);

	bInitialize = true;
}

void UC_OptionMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UC_OptionMenu::OnOffMenu()
{
	LoadSettings();

	bIsActive = true;

	SetVisibility(ESlateVisibility::Visible);
}

int UC_OptionMenu::GetResolutionScale()
{
	switch (ScreenScale.X)
	{
	case 1024:
		return 0;
	case 1366:
		return 1;
	case 1920:
		return 2;
	}
	return 0;
}

void UC_OptionMenu::LoadSettings()
{
	ResolutionScale->SetSelectedIndex(GetResolutionScale());
	FullScreenCheckBox->SetIsChecked(bIsChecked);
	AntiAliasing->SetSelectedIndex(GameUserSettings->GetAntiAliasingQuality());
	PostProcessing->SetSelectedIndex(GameUserSettings->GetPostProcessingQuality());
	Shadows->SetSelectedIndex(GameUserSettings->GetShadowQuality());
	Textures->SetSelectedIndex(GameUserSettings->GetTextureQuality());
	Shading->SetSelectedIndex(GameUserSettings->GetShadingQuality());
}

void UC_OptionMenu::AddOption(UComboBoxString* BoxName)
{
	BoxName->AddOption("Low");
	BoxName->AddOption("Medium");
	BoxName->AddOption("High");
	BoxName->AddOption("Epic");
	BoxName->AddOption("Cinematic");
}

void UC_OptionMenu::SetResoultionScale(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	switch (ResolutionScale->GetSelectedIndex())
	{
	case 0:
		ScreenScale = { 1024, 768 };
		break;
	case 1:
		ScreenScale = { 1366, 768 };
		break;
	case 2:
		ScreenScale = { 1920, 1200 };
		break;
	}
}

void UC_OptionMenu::SetFullScreenMode(bool bIsCheck)
{
	bIsChecked = !bIsChecked;
}

void UC_OptionMenu::SetAntiAliasingOption(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	Index[0] = AntiAliasing->GetSelectedIndex();
}

void UC_OptionMenu::SetPostProcessingOption(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	Index[1] = PostProcessing->GetSelectedIndex();
}

void UC_OptionMenu::SetShadowsOption(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	Index[2] = Shadows->GetSelectedIndex();
}

void UC_OptionMenu::SetTexturesOption(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	Index[3] = Textures->GetSelectedIndex();
}

void UC_OptionMenu::SetShadingOption(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	Index[4] = Shading->GetSelectedIndex();
}

void UC_OptionMenu::ClickedSaveButton()
{
	CLog::Print("ClickedSaveButton");

	GameUserSettings->SetScreenResolution(ScreenScale);
	GameUserSettings->SetAntiAliasingQuality(Index[0]);
	GameUserSettings->SetPostProcessingQuality(Index[1]);
	GameUserSettings->SetShadowQuality(Index[2]);
	GameUserSettings->SetTextureQuality(Index[3]);
	GameUserSettings->SetShadingQuality(Index[4]);

	if (bIsChecked)
		GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	else
		GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);

	bIsActive = false;

	GameUserSettings->ApplySettings(false);

	SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UC_OptionMenu::ClickedCancelButton()
{
	bIsActive = false;

	SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}