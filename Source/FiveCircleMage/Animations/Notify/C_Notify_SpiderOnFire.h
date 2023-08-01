#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_Notify_SpiderOnFire.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_Notify_SpiderOnFire : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UC_Notify_SpiderOnFire();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

};
