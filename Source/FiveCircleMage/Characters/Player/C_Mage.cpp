#include "Characters/Player/C_Mage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

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

    /*ElementPanel = CreateWidget<UUserWidget>(this, WidgetClass);
    if (ElementPanel != nullptr)
    {
        ElementPanel->AddToViewport();
        ElementPanel->SetVisibility(ESlateVisibility::Hidden);
    }*/

    //ElementPanel = GetController()->GetElementPanel();
}

void AC_Mage::BeginPlay()
{
    Super::BeginPlay();

    GenericTeamID = 1;
}

void AC_Mage::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DirectionState = EDirectionState::None;

    {
        FVector location = GetActorLocation();
        FVector dest = MouseLocation;
        dest.Z = location.Z;

        FRotator rot = (dest - location).Rotation();
        SetActorRotation(rot);
        //LookDirection = dest - location;
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
    input->BindAction(InputActions.FindRef(L"AssembleElement"), ETriggerEvent::Triggered, this, &AC_Mage::OnAssembleElement);

    input->BindAction(InputActions.FindRef(L"OnElementPanel"), ETriggerEvent::Triggered, this, &AC_Mage::OnElementPanel);
}

#pragma region Bind Action Function
void AC_Mage::OnDash()
{
    if (IsDash) return;

    CLog::Print(L"OnDash");

    FVector velocity = GetVelocity();
    if (velocity == FVector::ZeroVector)
        velocity = FVector(1.0f, 0, 0);

    velocity.Z = 0.0f;
    velocity.Normalize();

    float power = 2000.0f;
    velocity *= power;
    velocity.Z = 100.0f;

    LaunchCharacter(velocity, true, false);

    IsDash = true;
}

void AC_Mage::OnMagicCast()
{
    CLog::Print(L"OnMagicCast");

    //FDebuffInfo debuff;

    //debuff.DebuffType = EUnitState::Slow;
    //debuff.Value = 10.0f;
    //debuff.Interval = 0.5f;
    //debuff.Time = 3.0f;

    //DamageComponent->SetDebuff(this, debuff);
}

void AC_Mage::OnAssembleElement()
{
    CLog::Print(L"OnAssembleElement");
}
#pragma endregion

#pragma region Bind Axis Function
void AC_Mage::ForwardMove(const FInputActionInstance& Instance)
{
    FVector value = Instance.GetValue().Get<FVector>();

    if (value.X > 0)
        DirectionState = EDirectionState::Forward;
    else
        DirectionState = EDirectionState::Back;

    CLog::Print(static_cast<float>(value.X));

    if (IsDash) return;

    AddMovementInput(FORWARD * UnitStatus.GetCurMoveSpeed(), value.X);
}

void AC_Mage::RightMove(const FInputActionInstance& Instance)
{
    FVector value = Instance.GetValue().Get<FVector>();

    if (DirectionState == EDirectionState::Forward)
    {
        if (value.X > 0)
            DirectionState = EDirectionState::Forward_Right;
        else if (value.X < 0)
            DirectionState = EDirectionState::Forward_Left;
    }

    else if (DirectionState == EDirectionState::Back)
    {
        if (value.X > 0)
            DirectionState = EDirectionState::Back_Right;
        else if (value.X < 0)
            DirectionState = EDirectionState::Back_Left;
    }

    else if (DirectionState == EDirectionState::None)
    {
        if (value.X > 0)
            DirectionState = EDirectionState::Right;
        else if (value.X < 0)
            DirectionState = EDirectionState::Left;
    }

    if (IsDash) return;

    AddMovementInput(RIGHT * UnitStatus.GetCurMoveSpeed(), value.X);
}
#pragma endregion 

#pragma region Casting Magic Skill Func
///////////////////////////////////////////////////////////
// Code: void OnElementPanel()
// Desc: Manage input key about element panel
//////////////////////////////////////////////////////////
void AC_Mage::OnElementPanel(const FInputActionInstance& Instance)
{
    bool bCheck = Instance.GetValue().Get<bool>();

    if (bCheck == true)
        OpenElementPanel();
    else
        CloseElementPanel();
}

///////////////////////////////////////////////////////////
// Code: void OpenElementPanel()
// Desc: Open element panel
//////////////////////////////////////////////////////////
void AC_Mage::OpenElementPanel()
{
    //ElementPanel->ShowPanel();
}

///////////////////////////////////////////////////////////
// Code: void CloseElementPanel()
// Desc: Close element panel and insert element to stacks
//////////////////////////////////////////////////////////
void AC_Mage::CloseElementPanel()
{
    ECastingElement InputedElement = ECastingElement::None;

    // 여기에 선택된 원소 판별 필요
    //ElementPanel->HidePanel(InputedElement);

    if (CastingStack.BeginCasting(InputedElement))
    {
        // Casting animation execute
    }
    else
    {
        // Casting break animation execute
    }
}

///////////////////////////////////////////////////////////
// Code: void GetCastingStack()
// Desc: Return casting stack data for aligning stack on UI
//////////////////////////////////////////////////////////
void AC_Mage::GetCastingStack(OUT TArray<ECastingElement>* UICastingStack)
{
    CastingStack.GetUnsortedCastingStack(UICastingStack);
}

///////////////////////////////////////////////////////////
// Code: void Casting()
// Desc: Casting magic skill
//////////////////////////////////////////////////////////
void AC_Mage::Casting()
{

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
