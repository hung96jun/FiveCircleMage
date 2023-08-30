#include "Animations/NotifyState/C_NotifyState_OnFireParabolation.h"
#include "Components/CapsuleComponent.h"

#include "Characters/Monster/C_Monster.h"
#include "Weapons/Weapon/C_ThrowingWeapon.h"
//#include "Weapons/Weapon/ThrowingWeapons/C_SpiderSaliva.h"

#include "C_GameInstance.h"
#include "Managers/C_WeaponManager.h"

#include "Utilities/CLog.h"


void UC_NotifyState_OnFireParabolation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;
	if (SocketName == L"")
	{
		CLog::Print(L"Error - UC_NotifyState_OnFireParabolation class, socket name is None", 1000.0f, FColor::Red);
		return;
	}

	AC_Monster* owner = Cast<AC_Monster>(MeshComp->GetOwner());
	if (owner == nullptr) return;

	Height = owner->GetActorLocation().Z;

	bTargetTrace = false;
	Result.Reset();
}

void UC_NotifyState_OnFireParabolation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;
	if (bTargetTrace == true) return;
	if (SocketName == L"")
	{
		CLog::Print(L"Error - UC_NotifyState_OnFireParabolation class, socket name is None", 1000.0f, FColor::Red);
		return;
	}

	AC_Monster* owner = Cast<AC_Monster>(MeshComp->GetOwner());
	if (owner == nullptr) return;

	FVector start, velocity;
	start = owner->GetActorLocation();
	velocity = owner->GetActorForwardVector();
	velocity *= Distance;
	velocity.Z += Height;

	FPredictProjectilePathParams params;
	params.StartLocation = start;
	params.LaunchVelocity = velocity;
	params.ProjectileRadius = 20.0f;
	params.SimFrequency = Distance* RadiusRatio;
	params.bTraceWithCollision = true;
	params.bTraceWithChannel = true;
	params.ActorsToIgnore.Add(owner);
	params.DrawDebugType = (bDebug == true) ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;

	bool bHit = UGameplayStatics::PredictProjectilePath(owner->GetWorld(), params, Result);

	if (bHit == true)
	{
		for (int i = 0; i < TargetClasses.Num(); i++)
		{
			if (Result.HitResult.GetActor()->GetClass() == TargetClasses[i])
			{
				AC_Unit* target = Cast<AC_Unit>(Result.HitResult.GetActor());
				if (target == nullptr)
					continue;

				bTargetTrace = true;

				break;
			}
		}
	}

	Height += ZInterval;
}

void UC_NotifyState_OnFireParabolation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner() == nullptr) return;
	if (bTargetTrace == false) return;
	if (SocketName == L"")
	{
		CLog::Print(L"Error - UC_NotifyState_OnFireParabolation class, socket name is None", 1000.0f, FColor::Red);
		return;
	}
	AC_Monster* owner = Cast<AC_Monster>(MeshComp->GetOwner());
	if (owner == nullptr) 
	{
		CLog::Print(L"ParabolationNotifyState - Owner nullptr", 1000.0f, FColor::Red);
		return;
	}

	UC_GameInstance* instance = Cast<UC_GameInstance>(owner->GetWorld()->GetGameInstance());
	if (instance == nullptr)
	{
		CLog::Print(L"Error - UC_NotifyState_OnFireParabolation class, GameInstance class is nullptr", 1000.0f, FColor::Red);
		return;
	}
	if (instance->GetWeaponManager() == nullptr)
	{
		CLog::Print(L"Error - UC_NotifyState_OnFireParabolation class, WeaponManager class is nullptr", 1000.0f, FColor::Red);
		return;
	}
	if (instance->GetWeaponManager()->FindWeapon(WeaponName) == false)
	{
		CLog::Print(L"Error - UC_NotifyState_OnFireParabolation class, WeaponName find failed", 1000.0f, FColor::Red);
		return;
	}

	//AC_SpiderSaliva* object = owner->GetWorld()->SpawnActor<AC_SpiderSaliva>();
	AC_ThrowingWeapon* object = Cast<AC_ThrowingWeapon>(instance->GetWeaponManager()->ActiveWeapon(WeaponName));
	if (object == nullptr)
	{
		CLog::Print(L"ParabolationNotifyState - SpiderSaliva Spawn Failed", 1000.0f, FColor::Red);
		return;
	}
	
	FVector spawnLocation = MeshComp->GetSocketLocation(SocketName);// +owner->GetActorLocation();
	FVector direction = owner->GetActorForwardVector() * 100.0f;
	spawnLocation.X += direction.X;
	spawnLocation.Y += direction.Y;
	spawnLocation.Z += 100.0f;
	object->SetActorLocation(spawnLocation);

	FVector velocity = Result.HitResult.Location - owner->GetActorLocation();
	velocity.Z = Height + TempZValue;

	object->OnFire(velocity, owner);
}
