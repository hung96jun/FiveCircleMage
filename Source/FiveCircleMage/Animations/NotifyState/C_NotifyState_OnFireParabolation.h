#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_NotifyState_OnFireParabolation.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API UC_NotifyState_OnFireParabolation : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bDebug = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName SocketName = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString WeaponName = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ZInterval = 10.0f;

	/*
	* Z Value to be incremented per DeltaTime
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TempZValue = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Distance = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<AActor>> TargetClasses;

private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	FPredictProjectilePathResult Result;
	FVector Direction;

	bool bTargetTrace = false;

	float Height = 0.0f;
	float RadiusRatio = 0.02f;
};
