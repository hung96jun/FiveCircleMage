#include "Characters/Player/C_Mage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

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
}

void AC_Mage::BeginPlay()
{
    Super::BeginPlay();

    GenericTeamID = 1;

    DashDelegate.BindUFunction(this, "EndDash");

    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AC_Mage::TestFunction1);
}

void AC_Mage::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DirectionState = EDirectionState::None;

    if (bCasting == true)
        CLog::Print(L"Casting : true", 0.01f, FColor::Cyan);
    else
        CLog::Print(L"Casting : false", 0.01f, FColor::Cyan);

    if (bCastingBreak == true)
        CLog::Print(L"CastingBreak : true", 0.01f, FColor::Cyan);
    else
        CLog::Print(L"CastingBreak : false", 0.01f, FColor::Cyan);
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
    //input->BindAction(InputActions.FindRef(L"AssembleElement"), ETriggerEvent::Triggered, this, &AC_Mage::OnAssembleElement);

    //input->BindAction(InputActions.FindRef(L"OnElementPanel"), ETriggerEvent::Triggered, this, &AC_Mage::OnElementPanel);
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
    TArray<ECastingElement> elements;
    CastingStack.GetUnsortedCastingStack(&elements);

    if (CastingStack.BeginCasting(Element) == true)
    {
        bCasting = true;
    }
    else
    {
        bCasting = false;
        bCastingBreak = true;
    }

    CLog::Print(L"----------------------", 10.0f, FColor::Cyan);
    for (ECastingElement element : elements)
    {
        CLog::Print(UC_CastingElement::EnumToString(element), 10.0f, FColor::Cyan);
    }
    CLog::Print(L"----------------------", 10.0f, FColor::Cyan);
}

#pragma region Bind Action Function
void AC_Mage::OnDash()
{
    if (IsDash) return;

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

    IsDash = true;

    GetCapsuleComponent()->OnComponentHit.Clear();
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AC_Mage::TestFunction2);
}

void AC_Mage::EndDash()
{
    IsDash = false;
    CLog::Print(L"Call EndDash", 10.0f, FColor::Purple);
}

void AC_Mage::OnMagicCast()
{
    CLog::Print(L"OnMagicCast");

    if(CastingStack.IsCasting() == true)
    {
        bCasting = false;
        bOnFire = true;

        CastingStack.EndCasting();
    }
}

void AC_Mage::OnAssembleElement()
{
    bCastingBreak = true;
    bCasting = false;
}
#pragma endregion

#pragma region Bind Axis Function
void AC_Mage::ForwardMove(const FInputActionInstance& Instance)
{
    if (bCastingBreak == true) return;

    FVector value = Instance.GetValue().Get<FVector>();

    if (IsDash) return;

    AddMovementInput(FORWARD * UnitStatus.GetCurMoveSpeed(), value.X);
}

void AC_Mage::RightMove(const FInputActionInstance& Instance)
{
    if (bCastingBreak == true) return;

    FVector value = Instance.GetValue().Get<FVector>();

    if (IsDash) return;

    AddMovementInput(RIGHT * UnitStatus.GetCurMoveSpeed(), value.X);
}
#pragma endregion 

#pragma region Casting Magic Skill Func
/////////////////////////////////////////////////////////////
//// Code: void OnElementPanel()
//// Desc: Manage input key about element panel
////////////////////////////////////////////////////////////
//void AC_Mage::OnElementPanel(const FInputActionInstance& Instance)
//{
//    bool bCheck = Instance.GetValue().Get<bool>();
//
//    if (bCheck == true)
//        bCasting = true;
//}

/////////////////////////////////////////////////////////////
//// Code: void OpenElementPanel()
//// Desc: Open element panel
////////////////////////////////////////////////////////////
//void AC_Mage::OpenElementPanel()
//{
//    bCasting = true;
//    //ElementPanel->ShowPanel();
//}
//
/////////////////////////////////////////////////////////////
//// Code: void CloseElementPanel()
//// Desc: Close element panel and insert element to stacks
////////////////////////////////////////////////////////////
//void AC_Mage::CloseElementPanel()
//{
//    //ECastingElement InputedElement = ECastingElement::None;
//
//    //// 여기에 선택된 원소 판별 필요
//    //ElementPanel->HidePanel(InputedElement);
//
//    //if (CastingStack.BeginCasting(InputedElement))
//    //{
//    //    // Casting animation execute
//    //}
//    //else
//    //{
//    //    // Casting break animation execute
//    //}
//}

///////////////////////////////////////////////////////////
// Code: void GetCastingStack()
// Desc: Return casting stack data for aligning stack on UI
//////////////////////////////////////////////////////////
void AC_Mage::GetCastingStack(OUT TArray<ECastingElement>* UICastingStack)
{
    CastingStack.GetUnsortedCastingStack(UICastingStack);

    FVector test;
    test.GetSafeNormal();
}

///////////////////////////////////////////////////////////
// Code: void Casting()
// Desc: Casting magic skill
//////////////////////////////////////////////////////////
void AC_Mage::Casting()
{
    
}
void AC_Mage::TestFunction1(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    CLog::Print(L"Test1", 0.01f, FColor::Red);
}
void AC_Mage::TestFunction2(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    CLog::Print(L"Test2", 0.01f, FColor::Purple);
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

