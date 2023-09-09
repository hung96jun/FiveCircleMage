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

	//FVector start, velocity;
	//start = GetActorLocation();
	//velocity = GetActorForwardVector() * ProjectileDistance;
	//velocity.Z = start.Z;
	//velocity.Z += ProjectileHeight;

	//ProjectileParams.StartLocation = start;
	//ProjectileParams.LaunchVelocity = velocity;

	//FPredictProjectilePathResult hitResult;
	//bool bHit = UGameplayStatics::PredictProjectilePath(GetOwner(), 
	//	ProjectileParams, hitResult);

	//FString temp = L"";
	//temp = L"1. Spider HP : " + FString::SanitizeFloat((*GetUnitStatus()->GetCurHP()));
	//temp += L"\n2. Spider HP : " + FString::SanitizeFloat((*UnitStatus.GetCurHP()));
	//CLog::Print(temp, 0.01f, FColor::Blue);
}
