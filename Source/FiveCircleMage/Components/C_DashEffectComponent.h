#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_DashEffectComponent.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIVECIRCLEMAGE_API UC_DashEffectComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Offset = 0.0f;

public:	
	// Sets default values for this component's properties
	UC_DashEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetElement(const ECastingElement& Element);

	void OnEffect();

private:
	TArray<UNiagaraSystem*> DashEffects;

	UNiagaraSystem* SelectedEffect;
	UNiagaraComponent* EffectComponent;
};
