#include "Components/C_DashEffectComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#include "Enums/C_CastingElement.h"
#include "Utilities/Defines.h"

UC_DashEffectComponent::UC_DashEffectComponent()
{
	FString path;

	{//Empty
		path = "/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Ghost.NS_Dash_Ghost'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(*path);

		if (NS.Succeeded())
			DashEffects.Add(NS.Object);
	}

	{//Fire
		path = "/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Fire.NS_Dash_Fire'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(*path);

		if (NS.Succeeded())
			DashEffects.Add(NS.Object);
	}

	{//Ice
		path = "/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Mana.NS_Dash_Mana'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(*path);

		if (NS.Succeeded())
			DashEffects.Add(NS.Object);
	}

	{//Light
		path = "/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Paladin.NS_Dash_Paladin'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(*path);

		if (NS.Succeeded())
			DashEffects.Add(NS.Object);
	}

	{//Dark
		path = "/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Vampire.NS_Dash_Vampire'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(*path);

		if (NS.Succeeded())
			DashEffects.Add(NS.Object);
	}
}


void UC_DashEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UC_DashEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_DashEffectComponent::SetElement(const ECastingElement& Element)
{
	SelectedEffect = DashEffects[CAST(int, Element)];
}

void UC_DashEffectComponent::OnEffect()
{
	FVector direction = -GetOwner()->GetVelocity();
	FRotator rot = direction.Rotation();
	rot.Pitch = 0.0f;
	rot.Roll = 0.0f;

	UNiagaraFunctionLibrary::SpawnSystemAttached(SelectedEffect, GetOwner()->GetRootComponent(), "None",
		GetOwner()->GetActorLocation(), rot, EAttachLocation::KeepWorldPosition, true);
}
