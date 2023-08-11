#include "Characters/Player/C_Mage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetComponent.h"

#include "C_GameInstance.h"
#include "Managers/C_MagicManager.h"
#include "UI/C_DashProgressBar.h"
#include "Components/C_MagicDispenser.h"
#include "Components/C_DashEffectComponent.h"

#include "Utilities/CLog.h"

AC_Mage::AC_Mage()
{
    PrimaryActorTick.bCanEverTick = true;
    FString path = L"";

    {
        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_AssemblingElement.IA_AssemblingElement'";
        AddInputAction(L"AssembleElement", path);

        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_Dash.IA_Dash'";
        AddInputAction(L"Dash", path);

        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_MagicCast.IA_MagicCast'";
        AddInputAction(L"MagicCast", path);

        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_ForwardMove.IA_ForwardMove'";
        AddInputAction(L"ForwardMove", path);

        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_RightMove.IA_RightMove'";
        AddInputAction(L"RightMove", path);

        path = L"EnhancedInput.InputAction'/Game/Blueprint/Input/IA_OnElementPanel.IA_OnElementPanel'";
        AddInputAction(L"OnElementPanel", path);
    }

    {
        path = L"Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'";
        ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(*path);

        if (mesh.Succeeded())
            GetMesh()->SetSkeletalMesh(mesh.Object);

        FTransform transform;
        transform.SetLocation(FVector(0.0f, 0.0f, -90.0f));
        transform.SetRotation(FRotator(0.0f, -90.0f, 0.0f).Quaternion());
        GetMesh()->AddLocalTransform(transform);
    }

    {
        Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
        CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");

        CameraArm->SetupAttachment(RootComponent);
        Camera->SetupAttachment(CameraArm);

        CameraArm->TargetArmLength = 1000.0f;
        CameraArm->SocketOffset.X = 400.0f;
        CameraArm->SocketOffset.Z = 1000.0f;
        Camera->AddRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
        CameraArm->bUsePawnControlRotation = true;
        CameraArm->bInheritPitch = true;
        CameraArm->bInheritRoll = true;
        CameraArm->bInheritYaw = true;
        CameraArm->bDoCollisionTest = true;
        bUseControllerRotationYaw = true;
    }

    {
        Dispenser = CreateDefaultSubobject<UC_MagicDispenser>("Dispenser");
    }

    {
        DashEffectComponent = CreateDefaultSubobject<UC_DashEffectComponent>("DashEffectComponent");
    }

    {
        WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
        WidgetComp->SetupAttachment(RootComponent);

        path = L"UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/BpC_DashProgressBar.BpC_DashProgressBar_C'";
        ConstructorHelpers::FClassFinder<UC_DashProgressBar> widgetClass(*path);
        if (widgetClass.Succeeded())
        {
            WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
            WidgetComp->SetWidgetClass(widgetClass.Class);
            WidgetComp->SetDrawSize(FVector2D(200.0f, 50.0f));

            WidgetComp->AddRelativeLocation(FVector(0.0f, 0.0f, -220.0f));
        }
    }
}

void AC_Mage::BeginPlay()
{
    Super::BeginPlay();

    GenericTeamID = 1;

    DashDelegate.BindUFunction(this, "EndDash");
    DashCoolTimeDelegate.BindUFunction(this, "EndDashCoolTime");

    bDash = false;
    bDashCoolTime = false;

    Cast<UC_DashProgressBar>(WidgetComp->GetWidget())->SetDashCoolTime(DashCoolTime);
    Dispenser->SetOwner(this);

    ForceType = EUnitForceType::Player;
}

void AC_Mage::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DirectionState = EDirectionState::None;

    Dispenser->Update(DeltaTime);

    if (bEnablePushElement == false)
    {
        CurCastingDelayTime += DeltaTime;

        if (CurCastingDelayTime >= CastingDelay[CastingStack.StackSize()])
        {
            CurCastingDelayTime -= CastingDelay[CastingStack.StackSize()];
            bEnablePushElement = true;
        }
    }
}

void AC_Mage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (input == nullptr)
    {
        FString error = L"PlayerBase class : SetupPlayerInputComponent function - input value is nullptr";
        CLog::Print(error, 10.0f, FColor::Red);
        return;
    }

    input->BindAction(InputActions.FindRef(L"ForwardMove"), ETriggerEvent::Triggered, this, &AC_Mage::ForwardMove);
    input->BindAction(InputActions.FindRef(L"RightMove"), ETriggerEvent::Triggered, this, &AC_Mage::RightMove);

    input->BindAction(InputActions.FindRef(L"Dash"), ETriggerEvent::Triggered, this, &AC_Mage::OnDash);
    input->BindAction(InputActions.FindRef(L"MagicCast"), ETriggerEvent::Triggered, this, &AC_Mage::OnMagicCast);
}

void AC_Mage::GetDmg(const float Dmg, const EUnitState Type)
{
    Super::GetDmg(Dmg, Type);

    if (bCasting == true)
    {
        bCasting = false;
        bCastingBreak = true;
    }
}

void AC_Mage::PushCastingStack(const ECastingElement Element)
{
    DashEffectComponent->SetElement(Element);

    if (CastingStack.BeginCasting(Element) == true)
    {
        bCasting = true;
    }
    else
    {
        bCasting = false;
        bCastingBreak = true;
        DashEffectComponent->SetElement(ECastingElement::None);
    }
}

#pragma region Bind Action Function
void AC_Mage::OnDash()
{
    Cast<UC_DashProgressBar>(WidgetComp->GetWidget())->CallDashProgressBar();

    if (bDash == true || bDashCoolTime == true) return;

    CLog::Print(L"OnDash");

    FVector velocity = GetVelocity();
    if (velocity == FVector::ZeroVector)
        velocity = GetActorForwardVector() * -1.0f;

    velocity.Z = 0.0f;
    velocity.Normalize();

    float power = 2000.0f;
    velocity *= power;
    velocity.Z = 100.0f;

    LaunchCharacter(velocity, true, false);

    FTimerHandle dashTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(dashTimerHandle, DashDelegate, 0.5f, false);
    FTimerHandle dashCoolTimeHandle;
    GetWorld()->GetTimerManager().SetTimer(dashCoolTimeHandle, DashCoolTimeDelegate, DashCoolTime, false);

    bDash = true;
    bDashCoolTime = true;

    //DashEffectComponent->OnEffect();
}

void AC_Mage::EndDash()
{
    bDash = false;
}

void AC_Mage::EndDashCoolTime()
{
    bDashCoolTime = false;
}

void AC_Mage::OnMagicCast()
{
    CLog::Print(L"OnMagicCast");

    if (CastingStack.IsCasting() == true)
    {
        bCasting = false;
        bOnFire = true;

        DashEffectComponent->SetElement(ECastingElement::None);
        TArray<ECastingElement> castingElement;
        CastingStack.GetUnsortedCastingStack(&castingElement);
        Dispenser->CastMagic(castingElement, MouseLocation);
        CastingStack.EndCasting();
    }
}
#pragma endregion

#pragma region Bind Axis Function
void AC_Mage::ForwardMove(const FInputActionInstance& Instance)
{
    if (bCastingBreak == true) return;

    FVector value = Instance.GetValue().Get<FVector>();

    if (bDash) return;

    AddMovementInput(FORWARD * UnitStatus.GetCurMoveSpeed(), value.X);
}

void AC_Mage::RightMove(const FInputActionInstance& Instance)
{
    if (bCastingBreak == true) return;

    FVector value = Instance.GetValue().Get<FVector>();

    if (bDash) return;

    AddMovementInput(RIGHT * UnitStatus.GetCurMoveSpeed(), value.X);
}
#pragma endregion 

#pragma region Casting Magic Skill Func
///////////////////////////////////////////////////////////
// Code: void GetCastingStack()
// Desc: Return casting stack data for aligning stack on UI
//////////////////////////////////////////////////////////
void AC_Mage::GetCastingStack(OUT TArray<ECastingElement>* UICastingStack)
{
    CastingStack.GetUnsortedCastingStack(UICastingStack);
}
#pragma endregion

void AC_Mage::AddInputAction(FString Key, FString Path)
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

