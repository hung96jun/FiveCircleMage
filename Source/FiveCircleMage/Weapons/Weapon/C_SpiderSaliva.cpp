#include "Weapons/Weapon/C_SpiderSaliva.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


AC_SpiderSaliva::AC_SpiderSaliva()
{

}

void AC_SpiderSaliva::BeginPlay()
{
	Super::BeginPlay();

}

void AC_SpiderSaliva::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_SpiderSaliva::OnFire(const FVector& Start, const FVector& Target)
{
	FVector direction = Target - GetActorLocation();
	direction.Normalize();
	direction *= Speed;
	//Collision->AddImpulse()

	FPredictProjectilePathParams param;
	param.StartLocation = Start;
	param.LaunchVelocity = Target;
	
	//UGameplayStatics::PredictProjectilePath(GetWorld(), )
}

void AC_SpiderSaliva::SetParabolation(const FVector& Start, const FVector& End)
{
	FVector start = Start;
	FVector end = End;
	FVector center;
	
	float height = Height;

	Routes.Add(start);

	FVector direction = end - start;
	direction.Normalize();
	center = end - start;
	float distance = center.Size();
	center.Normalize();
	center = (center * (distance * 0.5f)) + start;
	center.Z += height;

	float weight = 1 / Precision;
	float t = 0.0f;

	for (int i = 0; i < Precision; i++)
	{
		t += weight;
				
	}

	Routes.Add(end);
}
