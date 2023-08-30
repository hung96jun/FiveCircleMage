// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notify/C_Notify_BossEndRangedAttack.h"

#include "Characters/Monster/Boss/C_Boss.h"
#include "Utilities/Defines.h"

void UC_Notify_BossEndRangedAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AC_Boss* Character = Cast<AC_Boss>(MeshComp->GetOwner());
	CheckNull(Character);

	Character->EndAttack();
	Character->EndRangedAttack();
}