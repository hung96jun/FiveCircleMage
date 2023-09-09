#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "C_SpawnTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_SpawnTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Key = L"";

protected:
	UFUNCTION()
		void OnBegin(AActor* OverlappedActor, AActor* OtherActor);

	//UFUNCTION()
	//	void OnEnd(AActor* OverlapeedActor, AActor* OtherActor);

public:
	AC_SpawnTriggerBox();

protected:
	virtual void BeginPlay() override;

private:
	bool bActive = true;
};
