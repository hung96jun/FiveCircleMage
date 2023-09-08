#include "Weapons/Magic/MesObjects/C_SanctuaryArea.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/Player/C_Mage.h"
#include "Characters/C_Unit.h"
#include "Weapons/Weapon/C_ThrowingWeapon.h"

AC_SanctuaryArea::AC_SanctuaryArea()
	: AC_MagicMes()
{
	FString path = L"/Script/Engine.Blueprint'/Game/Assets/Particles/Magic_Circle_Creator/Blueprints/BP_MagicCircleCreatorADV.BP_MagicCircleCreatorADV_C'";
	ConstructorHelpers::FClassFinder<AActor> effectClass(*path);
	if (effectClass.Succeeded())
	{
		EffectClass = effectClass.Class;
	}

	{
		//Collision->SetCapsuleHalfHeight(Radius);
		//Collision->SetCapsuleRadius(Radius);
		Collision->SetCollisionProfileName(L"SanctuaryArea");
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AC_SanctuaryArea::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_SanctuaryArea::OnBegin);

	EffectActor = Cast<AActor>(GetWorld()->SpawnActor(EffectClass));
	if (EffectActor == nullptr)
	{
		CLog::Print(L"SanctuaryArea - Effect Actor is nullptr");
		return;
	}

	EffectActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform); 
	EffectActor->SetActorRelativeLocation(FVector(0.0f, 0.0f, -160.0f));

	EffectActor->SetActorHiddenInGame(true);
}

void AC_SanctuaryArea::Tick(float DeltaTime)
{
	if (bActive == false) return;

	Super::Tick(DeltaTime);

}

void AC_SanctuaryArea::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	bActive = true;
	Duration = OriginDuration;

	SetActorLocation(TargetPosition);

	Collision->SetCapsuleHalfHeight(Radius);
	Collision->SetCapsuleRadius(Radius);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	EffectActor->SetActorHiddenInGame(false);
}

void AC_SanctuaryArea::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == this) return;
	if (OtherActor == OwnerActor) return;

	//AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);
	//if (IsOtherActor(OtherActor, otherUnit) == false) return;

	{
		AC_Unit* other = Cast<AC_Unit>(OtherActor);
		if (other != nullptr)
		{
			FVector location = GetActorLocation();
			FVector target = other->GetActorLocation();
			FVector velocity = target - location;
			float distance = velocity.Size();
			velocity.Normalize();
			float ratio = (Radius - distance) / Radius;
			ratio = FMath::Abs<float>(ratio);
			if (ratio < 0.2f)
				ratio = 0.2f;
			velocity *= (MaxPower * ratio);
			//velocity.Z = FMath::Lerp(MinHeight, MaxHeight, ratio);
			velocity.Z = MaxHeight;
			//velocity.Z *= 2.0f;
			//velocity *= ratio * 2.0f;
			//velocity.Z *= 100.0f;

			FString temp = L"";
			temp = other->GetActorLabel();
			temp += L" LaunchCharacter Velocity : " + velocity.ToString();
			CLog::Print(temp, 10.0f, FColor::Blue);

			other->GetCharacterMovement()->StopMovementImmediately();
			other->LaunchCharacter(velocity, false, false);
			return;
		}
	}

	{
		AC_ThrowingWeapon* other = Cast<AC_ThrowingWeapon>(OtherActor);
		if (other != nullptr)
		{
			if (OwnerActor->GetGenericTeamId() != other->GetTeamID())
			{
				other->OnHitAction();
			}
		}
	}
}

void AC_SanctuaryArea::EndActive()
{
	Super::EndActive();

	EffectActor->SetActorHiddenInGame(true);
}
