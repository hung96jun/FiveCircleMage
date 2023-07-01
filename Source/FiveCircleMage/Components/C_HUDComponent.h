#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_HUDComponent.generated.h"

class AC_Mage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIVECIRCLEMAGE_API UC_HUDComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_HUDComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AC_Mage* Character = nullptr;
};
