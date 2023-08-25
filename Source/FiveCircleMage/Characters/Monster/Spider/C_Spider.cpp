#include "Characters/Monster/Spider/C_Spider.h"

AC_Spider::AC_Spider()
{

}

void AC_Spider::BeginPlay()
{
	Super::BeginPlay();

}

void AC_Spider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start, velocity;
	start = GetActorLocation();
	velocity = GetActorForwardVector() * ProjectileDistance;
	velocity.Z = start.Z;
	velocity.Z += ProjectileHeight;

	ProjectileParams.StartLocation = start;
	ProjectileParams.LaunchVelocity = velocity;

	FPredictProjectilePathResult hitResult;
	bool bHit = UGameplayStatics::PredictProjectilePath(GetOwner(), 
		ProjectileParams, hitResult);
}

void AC_Spider::OnFireTrace()
{
	bEnableTrace = true;
}

void AC_Spider::OnFire()
{
	/*
	* TODO : Spawn spider saliva
	*/

	bEnableTrace = false;
}
