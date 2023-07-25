#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_Notify_TestString.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_Notify_TestString : public UAnimNotify
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Str = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FColor Color = FColor::Black;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Time = 10.0f;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
