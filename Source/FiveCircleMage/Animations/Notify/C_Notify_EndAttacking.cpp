#include "Animations/Notify/C_Notify_EndAttacking.h"

#include "Characters/Monster/C_Monster.h"
#include "Utilities/Defines.h"

void UC_Notify_EndAttacking::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;

	AC_Monster* character = Cast<AC_Monster>(MeshComp->GetOwner());
	CheckNull(character);

	character->ResetAttackState();
}
