#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_Notify_BossEndWeaponCollision.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_Notify_BossEndWeaponCollision : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
