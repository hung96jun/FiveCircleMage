#include "Animations/NotifyState/C_NotifyState_Attacking.h"

#include "Characters/Monster/C_Monster.h"


UC_NotifyState_Attacking::UC_NotifyState_Attacking()
{

}

void UC_NotifyState_Attacking::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;

	AC_Monster* owner = Cast<AC_Monster>(MeshComp->GetOwner());
	if (owner == nullptr) return;

	if (BoneName != L"")
		owner->AttachWeapon(BoneName, OffsetVector);

	owner->OnAttacking();
}

void UC_NotifyState_Attacking::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;

	AC_Monster* owner = Cast<AC_Monster>(MeshComp->GetOwner());
	if (owner == nullptr) return;

	owner->EndAttacking();
}
