#include "Components/C_UIComponent.h"

#include "UI/C_ElementPanel.h"
#include "UI/C_MainMenu.h"
#include "UI/C_OptionMenu.h"

#include "Global.h"

UC_UIComponent::UC_UIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_UIComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateUI();	
}

void UC_UIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_UIComponent::CallUI(FString key)
{
    Widgets[key]->SetVisibility(ESlateVisibility::Visible);
}

void UC_UIComponent::CreateUI()
{
    for (TPair<FString, TSubclassOf<UUserWidget>> classPair : WidgetClasses)
    {
        TPair<FString, UUserWidget*> pair;
        pair.Key = classPair.Key;
        pair.Value = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClasses.FindRef(classPair.Key));

        pair.Value->AddToViewport();
        pair.Value->SetVisibility(ESlateVisibility::Hidden);

        Widgets.Add(pair);
    }

    //ElementPanel = CreateWidget<UC_ElementPanel>(this, WidgetClasses.FindRef(L"ElementPanel"));
    //if (ElementPanel != nullptr)
    //{
    //    ElementPanel->AddToViewport();
    //
    //    ElementPanel->HidePanel();
    //    //ElementPanel->SetVisibility(ESlateVisibility::Hidden);
    //}
    //else
    //{
    //    CLog::Print(FString("Fuck you"));
    //}
    //
    //MainMenu = CreateWidget<UC_MainMenu>(this, WidgetClasses.FindRef(L"MainMenu"));
    ////MainMenu->SetOwner(this);
    //
    //OptionMenu = CreateWidget<UC_OptionMenu>(this, WidgetClasses.FindRef(L"OptionMenu"));
}
