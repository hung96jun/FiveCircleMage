#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_NotifyState_Attacking.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_NotifyState_Attacking : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName BoneName = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector OffsetVector = FVector::ZeroVector;

public:
	UC_NotifyState_Attacking();

private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	//virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

};
