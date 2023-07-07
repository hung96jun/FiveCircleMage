#include "Characters/Player/C_Mage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"


#include "Components/C_DamageComponent.h"


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
        DamageComponent = CreateDefaultSubobject<UC_DamageComponent>("TestComp");
    }
}

void AC_Mage::BeginPlay()
{
	Super::BeginPlay();

    //UnitStatus = FUnitStatus(10.0f, 500.0f);

    GenericTeamID = 1;
}

void AC_Mage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
}

#pragma region Bind Action Function
void AC_Mage::OnDash()
{
    CLog::Print(L"OnDash");

    FDebuffInfo debuff;

    debuff.DebuffType = EUnitState::Burn;
    debuff.Value = 10.0f;
    debuff.Interval = 0.5f;
    debuff.Time = 3.0f;

    DamageComponent->SetDebuff(this, debuff);
}

void AC_Mage::OnMagicCast()
{
    CLog::Print(L"OnMagicCast");

    FDebuffInfo debuff;

    debuff.DebuffType = EUnitState::Slow;
    debuff.Value = 0.5f;
    debuff.Interval = 2.9f;
    debuff.Time = 3.0f;

    DamageComponent->SetDebuff(this, debuff);
}

void AC_Mage::OnAssembleElement(const FInputActionInstance& Instance)
{
    CLog::Print(L"OnAssembleElement");
}
#pragma endregion

#pragma region Bind Axis Function
void AC_Mage::ForwardMove(const FInputActionInstance& Instance)
{
    FVector value = Instance.GetValue().Get<FVector>();

    AddMovementInput(FORWARD * UnitStatus.GetCurMoveSpeed(), value.X);
}

void AC_Mage::RightMove(const FInputActionInstance& Instance)
{
    FVector value = Instance.GetValue().Get<FVector>();

    AddMovementInput(RIGHT * UnitStatus.GetCurMoveSpeed(), value.X);
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
