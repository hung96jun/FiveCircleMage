// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_Notify_BossEndGroggy.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_Notify_BossEndGroggy : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	const int32 GroggyLoopTime = 3;
	int32 LoopTimeCount = 0;
};
