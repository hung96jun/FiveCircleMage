#include "Characters/Player/C_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Global.h"

#include "UI/C_ElementPanel.h"

AC_PlayerController::AC_PlayerController()
{
}

void AC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player))
    {
        if (UEnhancedInputLocalPlayerSubsystem* inputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputContext.IsNull() == false)
            {
                inputSystem->AddMappingContext(InputContext.LoadSynchronous(), 0);
            }
        }
    }

    ElementPanel = CreateWidget<UC_ElementPanel>(this, WidgetClass);
    if (ElementPanel != nullptr)
    {
        ElementPanel->AddToViewport();

        ElementPanel->HidePanel();
        //ElementPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        CLog::Print(FString("Fuck you"));
    }

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsFirstTick)
    {
        PushViewportSize();
    }
}

void AC_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void AC_PlayerController::PushViewportSize()
{
    FVector2D windowSize = CAST(FVector2D, GEngine->GameViewport->Viewport->GetSizeXY());

    ElementPanel->SetWindowSize(windowSize);
}
