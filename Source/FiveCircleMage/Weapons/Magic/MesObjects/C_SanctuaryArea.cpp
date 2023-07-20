#include "Weapons/Magic/MesObjects/C_SanctuaryArea.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/Player/C_Mage.h"

AC_SanctuaryArea::AC_SanctuaryArea()
	: AC_MagicMes()
{

}

void AC_SanctuaryArea::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_SanctuaryArea::OnBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AC_SanctuaryArea::OnEnd);
}

void AC_SanctuaryArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void AC_SanctuaryArea::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
//{
//}

void AC_SanctuaryArea::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == this) return;
	if (OtherActor == OwnerActor) return;

	AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);
	if (otherUnit == nullptr) return;
	if (otherUnit->GetForceType() == EUnitForceType::Player) return;

	FVector location = GetActorLocation();
	FVector otherLocation = otherUnit->GetActorLocation();

	FVector direction = otherLocation - location;
	direction.Z = 0.0f;
	float distance = direction.Size();
	direction.Z = 50.0f;
	direction.Normalize();

	float raidus = Collision->GetUnscaledCapsuleRadius();
	distance = raidus - distance;
	direction *= distance;

	otherUnit->LaunchCharacter(direction, true, true);
}

void AC_SanctuaryArea::OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AC_SanctuaryArea::EndActive()
{
	Super::EndActive();

}
