#include "Weapons/Magic/MesObjects/C_MagicLight.h"
#include "Components/PointLightComponent.h"

AC_MagicLight::AC_MagicLight()
{
	Light = CreateDefaultSubobject<UPointLightComponent>("Light");

	Light->SetupAttachment(RootComponent);

	Light->AddRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	Light->SoftSourceRadius = 1000.0f;
	Light->SourceLength = 1000.0f;
}

void AC_MagicLight::BeginPlay()
{
	Super::BeginPlay();

	//Light->SetActive(false);
	//Light->Intensity = 0.0f;
	Light->SetIntensity(0.0f);
}

void AC_MagicLight::Tick(float DeltaTime)
{
	if (bActive == false) return;

	Super::Tick(DeltaTime);

}

void AC_MagicLight::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	Super::BeginCasting(CasterPosition, TargetPosition, Rotation);
	
	MainParticle.GetComp()->SetVisibility(true);
	//Light->SetActive(true);
	//Light->Intensity = 8.0f;
	Light->SetIntensity(100000.0f);
}

void AC_MagicLight::EndActive()
{
	MainParticle.GetComp()->SetVisibility(false);
	//Light->SetActive(false);
	//Light->Intensity = 0.0f;
	Light->SetIntensity(0.0f);
}
