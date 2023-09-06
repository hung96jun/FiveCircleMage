#include "Characters/Player/C_PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Global.h"

#include "Components/C_UIComponent.h"
#include "UI/C_ElementPanel.h"
#include "UI/C_MainMenu.h"
#include "UI/C_OptionMenu.h"
#include "UI/C_PlayerHUD.h"
#include "UI/C_BossUI.h"
#include "Characters/Player/C_Mage.h"

#include "Characters/Monster/Boss/C_Boss.h"

AC_PlayerController::AC_PlayerController()
{
    FString path = L"";

    {
        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_AssemblingElement.IA_AssemblingElement'";
        AddInputAction(L"ElementPanel", path);

        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_PauseGame.IA_PauseGame'";
        AddInputAction(L"MainMenu", path);
    }

    UIComponent = CreateDefaultSubobject<UC_UIComponent>("UIComponent");
}

void AC_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

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

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    UIComponent->CallUI(L"PlayerHUD");
    UIComponent->GetUI<UC_PlayerHUD>(L"PlayerHUD")->SetHealth(Character->GetUnitStatus()->GetOriginHP(), Character->GetUnitStatus()->GetCurHP());
}

void AC_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Character == nullptr) return;

    //if (bIsFirstTick)
    //{
    //    PushViewportSize();
    //}

    // Ground mouse trace
    if(UGameplayStatics::IsGamePaused(GetWorld()) == false)
    {
        FVector start, end, direction;
        float distance = 4000.0f;
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

void AC_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(InputComponent);

    input->BindAction(InputActions.FindRef(L"ElementPanel"), ETriggerEvent::Triggered, this, &AC_PlayerController::OnOffElementPanel);
    input->BindAction(InputActions.FindRef(L"MainMenu"), ETriggerEvent::Triggered, this, &AC_PlayerController::OnOffMainMenu);

}

void AC_PlayerController::OpenBossUI(AC_Boss* Unit)
{
    UC_BossUI* bossUI = UIComponent->GetUI<UC_BossUI>("BossHUD");

    bossUI->Show(Unit->GetStatus());
    Unit->SetUI(bossUI);
}

void AC_PlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    Character = Cast<AC_Mage>(aPawn);
}

void AC_PlayerController::OnUnPossess()
{
    Super::OnUnPossess();

    CLog::Print(L"Call PlayerController - OnUnPossess function", 10.0f, FColor::Red);

    Character = nullptr;
}

void AC_PlayerController::AddInputAction(FString Key, FString Path)
{
    UInputAction* inputAction = nullptr;

    CHelpers::GetAsset(&inputAction, Path);

    if (inputAction != nullptr)
    {
        TPair<FString, UInputAction*> pair;
        pair.Key = Key;
        pair.Value = inputAction;

        InputActions.Add(pair);
    }
    else
    {
        FString error = L"Mage class : AddInputAction function - " + Key + L" InputAction Value is nullptr";
        CLog::Print(error, 1000.0f, FColor::Red);
    }
}

void AC_PlayerController::OnOffElementPanel(const FInputActionInstance& Instance)
{
    bool bCheck = Instance.GetValue().Get<bool>();
    
    if (bCheck == true)
        OpenElementPanel();
    else
        CloseElementPanel();
}

///////////////////////////////////////////////////////////
// Code: void OnElementPanel()
// Desc: Manage input key about element panel
//////////////////////////////////////////////////////////
void AC_PlayerController::OpenElementPanel()
{
    UC_ElementPanel* panel = UIComponent->GetUI<UC_ElementPanel>("ElementPanel");
    panel->ShowPanel();

    FVector2D windowSize = CAST(FVector2D, GEngine->GameViewport->Viewport->GetSizeXY());
    panel->SetWindowSize(windowSize);
}

///////////////////////////////////////////////////////////
// Code: void OpenElementPanel()
// Desc: Open element panel
//////////////////////////////////////////////////////////
void AC_PlayerController::CloseElementPanel()
{
    UC_ElementPanel* panel = UIComponent->GetUI<UC_ElementPanel>("ElementPanel");
    Character->PushCastingStack(panel->HidePanel());
}

void AC_PlayerController::OnOffMainMenu()
{
    UC_MainMenu* mainMenu = nullptr;

    mainMenu = UIComponent->GetUI<UC_MainMenu>("MainMenu");

    mainMenu->SetOptionMenu(UIComponent->GetUI<UC_OptionMenu>("OptionMenu"));

    mainMenu->SetOptionMenu(UIComponent->GetUI<UC_VolumeMenu>("VolumeMenu"));

    mainMenu->OnOffMenu();
}
