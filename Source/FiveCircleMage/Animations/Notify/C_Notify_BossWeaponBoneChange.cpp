#include "Animations/Notify/C_Notify_BossWeaponBoneChange.h"

#include "Characters/Monster/Boss/C_Boss.h"

void UC_Notify_BossWeaponBoneChange::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;

	AC_Boss* character = Cast<AC_Boss>(MeshComp->GetOwner());
	if (character == nullptr) return;

	character->WeaponChangeBone(BoneName, OffsetLocation, OffsetRotation);
}
