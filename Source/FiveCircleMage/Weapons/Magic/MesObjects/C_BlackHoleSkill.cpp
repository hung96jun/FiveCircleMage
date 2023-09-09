#include "Weapons/Magic/MesObjects/C_BlackHoleSkill.h"

#include "NiagaraFunctionLibrary.h"

AC_BlackHoleSkill::AC_BlackHoleSkill()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"";

	{
		path = L"/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/NiagaeaBigVFXPack/Effects/Niagara/Explosion/NS_Explosion_kira.NS_Explosion_kira'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);

		if (niagara.Succeeded())
			FlashEffect = niagara.Object;
	}
}

void AC_BlackHoleSkill::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AC_BlackHoleSkill::OnBegin);

	DelayTime = 3.0f;
	DamageInterval = 0.3f;
}

void AC_BlackHoleSkill::Tick(float DeltaTime)
{
	if (bActive == false) return;

	Super::Tick(DeltaTime);

	CurTime += DeltaTime;

	if (BlackHoleState == EBlackHoleState::Inhalation && CurTime <= DelayTime)
	{
		FVector scale = MainParticle.GetComp()->GetRelativeScale3D();
		scale -= scale * (DelayTime * (DeltaTime * 0.5f));
		MainParticle.GetComp()->SetRelativeScale3D(scale);
	}

	else if (BlackHoleState == EBlackHoleState::Inhalation && CurTime <= 0.5f)
	{
		//FVector scale = EndParticle.GetComp()->GetRelativeScale3D();
		//scale -= scale * (0.5 * DeltaTime);
		//EndParticle.GetComp()->SetRelativeScale3D(scale);
	}
}

void AC_BlackHoleSkill::BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation)
{
	Super::BeginCasting(CasterPosition, TargetPosition, Rotation);

	MainParticle.GetComp()->SetRelativeScale3D(FVector(1.0f));

	OnInhalation();
	DamageTimerDelegate.BindUFunction(this, "OnActive");
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegate, DamageInterval, true, DamageInterval);
	//if (GetWorld()->GetTimerManager().IsTimerActive(DamageTimerHandle))
	//	CLog::Print(L"BlackHole OnActive function not isActive", 10.0f, FColor::Red);
	//else
	//	CLog::Print(L"BlackHole OnActive function isActive", 10.0f, FColor::Blue);

	ChangeTimerDelegate.BindUFunction(this, "ChangeState");
	GetWorld()->GetTimerManager().SetTimer(ChangeTimerHandle, ChangeTimerDelegate, DelayTime, false);
	//if (GetWorld()->GetTimerManager().IsTimerActive(ChangeTimerHandle))
	//	CLog::Print(L"BlackHole ChangeState function not isActive", 10.0f, FColor::Red);
	//else
	//	CLog::Print(L"BlackHole ChangeState function isActive", 10.0f, FColor::Blue);

	FString temp = L"";

	if (Collision->OnComponentBeginOverlap.IsBound() == true)
		temp = L"BlackHole OnBegin bound true";
	else
		temp = L"BlackHole OnBegin bound false";

	//switch (Collision->GetCollisionEnabled())
	//{	
	//case ECollisionEnabled::NoCollision:
	//	temp += L"\nCollisionEnabled : NoCollision";
	//	break;
	//case ECollisionEnabled::QueryOnly:
	//	temp += L"\nCollisionEnabled : QueryOnly";
	//	break;
	//case ECollisionEnabled::PhysicsOnly:
	//	temp += L"\nCollisionEnabled : PhysicsOnly";
	//	break;
	//case ECollisionEnabled::QueryAndPhysics:
	//	temp += L"\nCollisionEnabled : QueryAndPhysics";
	//	break;
	//case ECollisionEnabled::ProbeOnly:
	//	temp += L"\nCollisionEnabled : ProbeOnly";
	//	break;
	//case ECollisionEnabled::QueryAndProbe:
	//	temp += L"\nCollisionEnabled : QueryAndProbe";
	//	break;
	//}

	//CLog::Print(temp, 10.0f, FColor::Cyan);
}

void AC_BlackHoleSkill::SetMagic(UNiagaraSystem* CopyMainParticle, FVector CopyMainLocation, FRotator CopyMainRotation, UNiagaraSystem* CopyEndParticle, FVector CopyEndLocation, FRotator CopyEndRotation, float Dmg, ESkillType Type, float LifeTime, EUnitState MagicProperty, float Speed)
{
	Super::SetMagic(CopyMainParticle, CopyMainLocation, CopyMainRotation, CopyEndParticle, CopyEndLocation, CopyEndRotation, Dmg, Type, LifeTime, MagicProperty, Speed);

	InhalationDamage = Damage * 0.1f;
	ExplosionDamage = Damage;
}

void AC_BlackHoleSkill::OnInhalation()
{
	BlackHoleState = EBlackHoleState::Inhalation;

	Damage = InhalationDamage;
}

void AC_BlackHoleSkill::OnExplosion()
{
	BlackHoleState = EBlackHoleState::Explosion;

	Damage = ExplosionDamage;
}

void AC_BlackHoleSkill::EndActive()
{
	Super::EndActive();

	BlackHoleState = EBlackHoleState::None;
	OtherUnits.Empty();
}

void AC_BlackHoleSkill::OnActive()
{
	FString temp = L"";
	temp += L"BlackHole Damage : " + FString::SanitizeFloat(Damage);
	CLog::Print(temp, 10.0f, FColor::Green);

	switch (BlackHoleState)
	{
	case EBlackHoleState::Inhalation:
	{
		FVector location = GetActorLocation();
		for (AC_Unit* unit : OtherUnits)
		{
			if ((*unit->GetUnitStatus()->GetCurHP()) < 0.0f) continue;

			FVector otherLocation = unit->GetActorLocation();
			FVector direction = location - otherLocation;
			direction.Z = 0.0f;
			float distance = direction.Size();
			direction.Normalize();
			direction *= distance;
			direction.Z = InhalationHeight;

			temp = unit->GetActorLabel();
			temp += L" - Launch Direction : " + direction.ToString();
			CLog::Print(temp, 1.0f, FColor::Cyan);
			
			{
				//unit->LaunchCharacter(direction, true, true);
				//UCapsuleComponent* comp = Cast<UCapsuleComponent>(unit->GetRootComponent());
				//if (comp == nullptr)
				//	CLog::Print(L"Error Comp", 10.0f, FColor::Red);
				//comp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				//comp->SetSimulatePhysics(true);
				//comp->AddImpulse(direction, L"None", true);
			}

			{
				unit->LaunchCharacter(direction * GravityPower, false, false);
			}

			DamageComp->GiveDmg(unit, Damage);
		}
	}
	break;
	case EBlackHoleState::Flash:
	{

	}
	break;
	case EBlackHoleState::Explosion:
	{
		for (AC_Unit* unit : OtherUnits)
		{
			CLog::Print(L"OnActive Explosion", 1.0f, FColor::Blue);

			if ((*unit->GetUnitStatus()->GetCurHP()) < 0.0f) return;

			FRotator rot = unit->GetActorRotation();
			rot.Pitch = 0.0f;
			rot.Roll = 0.0f;
			unit->SetActorRotation(rot);

			UCapsuleComponent* comp = Cast<UCapsuleComponent>(unit->GetRootComponent());
			if (comp == nullptr)
				CLog::Print(L"Error Comp", 10.0f, FColor::Red);
			comp->SetSimulatePhysics(false);
			comp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

			DamageComp->GiveDmg(unit, Damage);
		}

		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(ChangeTimerHandle);

		ChangeTimerDelegate.BindUFunction(this, "ChangeState");
		GetWorld()->GetTimerManager().SetTimer(ChangeTimerHandle, ChangeTimerDelegate, 0.5f, false);
	}
	break;
	}
}

void AC_BlackHoleSkill::ChangeState()
{
	if (BlackHoleState == EBlackHoleState::Inhalation)
	{
		MainParticle.GetComp()->SetVisibility(false);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FlashEffect, GetActorLocation());
		BlackHoleState = EBlackHoleState::Flash;

		ChangeTimerDelegate.BindUFunction(this, "ChangeState");
		GetWorld()->GetTimerManager().SetTimer(ChangeTimerHandle, ChangeTimerDelegate, 0.5f, false);
	}

	else if (BlackHoleState == EBlackHoleState::Flash)
	{
		OnExplosion();
		PlayParticle(END_PARTICLE);
		BlackHoleState = EBlackHoleState::Explosion;
		EndParticle.GetComp()->SetRelativeScale3D(FVector(0.5f));
		CurTime = 0.0f;
	}

	else if (BlackHoleState == EBlackHoleState::Explosion)
	{
		EndParticle.GetComp()->SetVisibility(false);
		GetWorld()->GetTimerManager().ClearTimer(ChangeTimerHandle);
	}
}

void AC_BlackHoleSkill::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_Unit* otherUnit = Cast<AC_Unit>(OtherActor);
	if (IsOtherActor(OtherActor, otherUnit) == false) return;

	OtherUnits.Add(otherUnit);
}
