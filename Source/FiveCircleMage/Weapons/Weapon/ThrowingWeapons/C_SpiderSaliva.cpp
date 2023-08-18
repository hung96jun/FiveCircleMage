#include "Weapons/Weapon/ThrowingWeapons/C_SpiderSaliva.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "C_SpiderSaliva.h"


AC_SpiderSaliva::AC_SpiderSaliva()
{
	FString path = L"";

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMesh");
	StaticMesh->SetupAttachment(Collision);

	path = L"/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'";
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(*path);
	if (mesh.Succeeded())
		StaticMesh->SetStaticMesh(mesh.Object);

	//Collision->SetSimulatePhysics(true);
	//StaticMesh->SetSimulatePhysics(true);

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Collision->SetCollisionProfileName(L"Magic");
}

void AC_SpiderSaliva::BeginPlay()
{
	Super::BeginPlay();

}

void AC_SpiderSaliva::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AC_SpiderSaliva::OnFire(const FVector& Target)
//{
//	Collision->SetSimulatePhysics(true);
//	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//
//	//Collision->AddImpulseAtLocation(GetActorLocation(), Target);
//	Collision->AddImpulse(Target, NAME_None, true);
//	//Collision->AddImpulseAtLocation(GetActorLocation(), Target);
//}

void AC_SpiderSaliva::OnHitAction()
{
	SetActorLocation(FVector::ZeroVector);
	Collision->SetSimulatePhysics(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AC_SpiderSaliva::SetActive(const bool Active)
{
	Super::SetActive(Active);

	if (Active == false)
	{
		StaticMesh->SetHiddenInGame(true);
	}
	else
	{
		StaticMesh->SetHiddenInGame(false);
	}
}
