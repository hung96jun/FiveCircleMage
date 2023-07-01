#include "Components/C_HUDComponent.h"

#include "Characters/Player/C_Mage.h"


UC_HUDComponent::UC_HUDComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UC_HUDComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UC_HUDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

