#include "Animations/Notify/C_Notify_MagicCast.h"

#include "Characters/Player/C_Mage.h"

#include "Utilities/Defines.h"

#include "NiagaraSystem.h"

void UC_Notify_ResetOnFire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	NotifyCheck();
	AC_Mage* character = Cast<AC_Mage>(MeshComp->GetOwner());
	CheckNull(character);

	character->ResetOnFire();
}

void UC_Notify_ResetBreakCasting::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	NotifyCheck();
	AC_Mage* character = Cast<AC_Mage>(MeshComp->GetOwner());
	CheckNull(character);

	character->ResetCastingBreak();
}

void UC_Notify_ResetCasting::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	NotifyCheck();
	AC_Mage* character = Cast<AC_Mage>(MeshComp->GetOwner());
	CheckNull(character);

	character->ResetCasting();
}
