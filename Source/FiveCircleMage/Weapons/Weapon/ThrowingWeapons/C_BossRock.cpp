#include "Weapons/Weapon/ThrowingWeapons/C_BossRock.h"

AC_BossRock::AC_BossRock()
{
	FString path = L"/Script/Engine.StaticMesh'/Game/KiteDemo/Environments/Rocks/Mountain_RockFace_002/SM_MountainRock_Closed.SM_MountainRock_Closed'";
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(*path);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");

	if (mesh.Succeeded())
	{
		MeshComp->SetStaticMesh(mesh.Object);
		MeshComp->SetupAttachment(RootComponent);
		MeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));	
		MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	}

	PrimaryActorTick.bCanEverTick = true;
}

void AC_BossRock::BeginPlay()
{
	Super::BeginPlay();

	Collision->SetCapsuleHalfHeight(80.0f);
	Collision->SetCapsuleRadius(80.0f);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActive(false);
}

void AC_BossRock::Tick(float DeltaTime)
{
	CurLifeTime += DeltaTime;
	if (CurLifeTime >= MaxLifeTime) SetActive(false);
	if (bActive == false) return;

	Super::Tick(DeltaTime);

	AccelatingInterval += AccelatingInterval * DeltaTime;
	Speed += AccelatingInterval * DeltaTime;

	FVector location = GetActorLocation() + FireDirection * Speed;

	SetActorLocation(location);
	SetActorRotation(GetActorRotation() + FRotator(0.0f, 0.0f, Speed * DeltaTime));
}

void AC_BossRock::OnFire(const FVector& Target, AC_Unit* Actor)
{
	SetActive(true);
	SetOwnerActor(Actor);

	FireDirection = Target.GetSafeNormal();
	SetActorLocation(Actor->GetActorLocation() + Actor->GetActorForwardVector() * 250.0f);
		
	Speed = OriginSpeed;
	AccelatingInterval = OriginAccelatingInterval;
	CurLifeTime = 0.0f;
}

void AC_BossRock::OnHitAction()
{
	Super::OnHitAction();

	SetActive(false);
}

void AC_BossRock::SetActive(const bool Value)
{
	bActive = Value;
	SetActorHiddenInGame(!Value);
	
	if (Value)
		SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
	{
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetActorLocation(FVector::ZeroVector);
	}
}