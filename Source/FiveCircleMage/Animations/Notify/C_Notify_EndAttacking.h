#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_Notify_EndAttacking.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_Notify_EndAttacking : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
