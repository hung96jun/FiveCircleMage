#include "Characters/Player/C_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

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
}

void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}
