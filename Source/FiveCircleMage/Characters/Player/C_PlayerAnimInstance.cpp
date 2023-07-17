#include "Characters/Player/C_PlayerAnimInstance.h"
#include "KismetAnimationLibrary.h"


#include "Characters/Player/C_Mage.h"

UC_PlayerAnimInstance::UC_PlayerAnimInstance()
{

}

void UC_PlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<AC_Mage>(TryGetPawnOwner());
}

void UC_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character == nullptr) return;

	Super::NativeUpdateAnimation(DeltaSeconds);
	
	MoveSpeed = Character->GetVelocity().Size();

	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
	Direction -= Character->GetActorRotation().Yaw;

	DirectionState = Character->GetDirectionState();

	IsDash = Character->GetIsDash();
}