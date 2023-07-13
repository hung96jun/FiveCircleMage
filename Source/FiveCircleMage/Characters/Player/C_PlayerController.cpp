#include "Characters/Player/C_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Global.h"

#include "UI/C_ElementPanel.h"
#include "Characters/Player/C_Mage.h"

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
        Character->SetElementPanel(ElementPanel);
    }

    // Ground mouse trace
    {
        FVector start, end, direction;
        float distance = 2000.0f;
        DeprojectMousePositionToWorld(start, direction);
        end = start + (direction * distance);

        TArray<AActor*> ignores;
        ignores.Add(Character);

        FHitResult result;

        bool bTrace = UKismetSystemLibrary::LineTraceSingle
        (
            GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1,
            false, ignores, EDrawDebugTrace::ForOneFrame, result, true
        );

        if (bTrace == true)
        {
            //Character->SetMouseLocation(result.Location);
            FVector location = Character->GetActorLocation();
            FVector dest = result.Location;
            dest.Z = location.Z;

            FRotator rot = (dest - location).Rotation();
            Character->SetActorRotation(rot);
            Character->SetMouseLocation(dest);
        }
    }
}

void AC_PlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    Character = Cast<AC_Mage>(aPawn);
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
