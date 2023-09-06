#include "Weapons/Weapon/ThrowingWeapons/C_SpiderSaliva.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "C_SpiderSaliva.h"


AC_SpiderSaliva::AC_SpiderSaliva()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"";

	{
		path = L"/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/RPGEffects/ParticlesNiagara/Mage/Fireball/NS_Mage_Fireball.NS_Mage_Fireball'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);

		if (niagara.Succeeded())
			Particle = niagara.Object;
	}

	Collision->SetCollisionProfileName(L"Magic");
}

void AC_SpiderSaliva::BeginPlay()
{
	Super::BeginPlay();

	if (ParticleComponent == nullptr)
		CLog::Print(L"SpiderSaliva ParticleComp is nullptr", 1000.0f, FColor::Red);
	else
		CLog::Print(L"SpiderSaliva ParticleComp is not nullptr", 1000.0f, FColor::Green);
}

void AC_SpiderSaliva::Tick(float DeltaTime)
{
	if (bActive == false) return;

	Super::Tick(DeltaTime);

}

void AC_SpiderSaliva::OnHitAction()
{
	if (ParticleComponent == nullptr)
	{
		CLog::Print(L"SpiderSaliva Particle is nullptr", 10.0f, FColor::Red);
		return;
	}

	ParticleComponent->Deactivate();

	SetActorLocation(FVector::ZeroVector);
	Collision->SetSimulatePhysics(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AC_SpiderSaliva::SetActive(const bool Active)
{
	Super::SetActive(Active);

	//if (Active == false)
	//{
	//	StaticMesh->SetHiddenInGame(true);
	//}
	//else
	//{
	//	StaticMesh->SetHiddenInGame(false);
	//}
}

void AC_SpiderSaliva::OnFire(const FVector& Target, AC_Unit* Actor)
{
	Super::OnFire(Target, Actor);

	ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(Particle,
		Collision, L"None", FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset, true);

	if (ParticleComponent == nullptr)
	{
		CLog::Print(L"SpiderSaliva ParticleComponent == nullptr", 100.0f, FColor::Red);
		return;
	}

	ParticleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
