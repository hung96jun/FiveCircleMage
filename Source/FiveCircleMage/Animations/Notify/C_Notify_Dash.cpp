// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notify/C_Notify_Dash.h"

#include "Characters/Player/C_Mage.h"

//////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////

void UC_Notify_Dash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;

	AC_Mage* character = Cast<AC_Mage>(MeshComp->GetOwner());

	if (character == nullptr) return;

	character->EndDash();
}
