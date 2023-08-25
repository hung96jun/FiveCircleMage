// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_MainMenu.h"
#include "Components/Button.h"

#include "Characters/Player/C_PlayerController.h"
#include "UI/C_OptionMenu.h"
#include "UI/C_VolumeMenu.h"

#include "Characters/Player/C_Mage.h"

UC_MainMenu::UC_MainMenu(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
}

void UC_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//생성자 : Event를 Binding 하기위함
	
	//if (ResumeButton->OnClicked.IsBound() == true)
	//	ResumeButton->OnClicked.Clear();
	//ResumeButton->OnClicked.AddDynamic(this, &UC_MainMenu::ClickedResumeButton);

	if (ResumeButton->OnClicked.IsBound() == true)
		ResumeButton->OnClicked.Clear();
	ResumeButton->OnClicked.AddDynamic(this, &UC_MainMenu::OnOffMenu);

	if (GrafficOptionButton->OnClicked.IsBound() == true)
		GrafficOptionButton->OnClicked.Clear();
	GrafficOptionButton->OnClicked.AddDynamic(this, &UC_MainMenu::ClickedGrafficOptionButton);

	if (SoundOptionButton->OnClicked.IsBound() == true)
		SoundOptionButton->OnClicked.Clear();
	SoundOptionButton->OnClicked.AddDynamic(this, &UC_MainMenu::ClickedSoundOptionButton);

	
	if (ExitButton->OnClicked.IsBound() == true)
		ExitButton->OnClicked.Clear();
	ExitButton->OnClicked.AddDynamic(this, &UC_MainMenu::ClickedExitButton);

	//if(ResumeButton->OnClicked.IsBound() == true)
	//	CLog::Print(L"ResumeButton function binding success", 10.0f, FColor::Red);
	//else
	//	CLog::Print(L"ResumeButton function binding failed", 10.0f, FColor::Red);
	//
	//
	//if (ExitButton->OnClicked.IsBound() == true)
	//	CLog::Print(L"ExitButton function binding success", 10.0f, FColor::Red);
	//else
	//	CLog::Print(L"ExitButton function binding failed", 10.0f, FColor::Red);
}

void UC_MainMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	//sif (ResumeButton->OnClicked.IsBound() == true)
	//s	CLog::Print(L"ResumeButton function binding", 0.0f, FColor::Green);
	//selse
	//s	CLog::Print(L"ResumeButton function not binding", 10.0f, FColor::Green);

}

void UC_MainMenu::OnOffMenu()
{
	if (OptionMenu->IsActive()) return;
	if (VolumeMenu->IsActive()) return;

	bIsActive = !bIsActive;

	UGameplayStatics::SetGamePaused(GetWorld(), bIsActive);

	if (bIsActive == true)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}

void UC_MainMenu::ClickedGrafficOptionButton()
{
	bIsActive = false;

	SetVisibility(ESlateVisibility::Hidden);

	OptionMenu->OnOffMenu();
}

void UC_MainMenu::ClickedSoundOptionButton()
{
	bIsActive = false;

	SetVisibility(ESlateVisibility::Hidden);

	VolumeMenu->OnOffMenu();
}

void UC_MainMenu::ClickedExitButton()
{
	bIsActive = false;

	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
