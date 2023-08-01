#include "Components/C_MagicDispenser.h"
#include "Global.h"
#include "Math/UnrealMathUtility.h"
#include "C_GameInstance.h"
#include "Managers/C_MagicManager.h"
#include "Weapons/Magic/C_MagicSkill.h"

UC_MagicDispenser::UC_MagicDispenser()
{
	ElementTray.SetNum(5);

	SetSkills();
}

void UC_MagicDispenser::BeginPlay()
{
	Super::BeginPlay();
}

void UC_MagicDispenser::InitCasting()
{
	for (int32& cnt : ElementTray)
		cnt = 0;

	MagicKey = "";
	TargetLocation = FVector::ZeroVector;
}

void UC_MagicDispenser::SetMagicProperty()
{
	bool isBasicMagic = ElementTray[1] + ElementTray[2] > 0;

	if (ElementTray[CAST(int32, ECastingElement::Light)] > 0 && isBasicMagic)
	{
		SetMultiple();
	}
	else if (ElementTray[CAST(int32, ECastingElement::Dark)] > 0 && isBasicMagic)
	{
		SetDarkness();
	}
	else
	{
		SpawnMagic(MagicKey, Owner->GetActorLocation(), TargetLocation, Owner->GetActorRotation());
	}
}

void UC_MagicDispenser::SetMultiple()
{
	FVector curOwnerLocation = Owner->GetActorLocation();
	FRotator curOwnerRotation = Owner->GetActorRotation();

	AC_MagicSkill* curCastingMagicSkill = nullptr;
	curCastingMagicSkill = SpawnMagic(MagicKey, curOwnerLocation, TargetLocation, curOwnerRotation);

	if (curCastingMagicSkill == nullptr)
	{
		CLog::Print("curCastingMagicSkill is nullptr!! - SetMultiple()");
		return;
	}

	TArray<FVector> extraLocation;
	TArray<FRotator> extraRotation;
	ESkillType type = curCastingMagicSkill->GetMagicType();
	
	switch (type)
	{
	case ESkillType::Missile:
		for (int32 index = 1; index <= ElementTray[CAST(int32, ECastingElement::Light)]; index++)
		{
			FVector tmpLocation = TargetLocation - Owner->GetActorRightVector() * 100 * index;
			tmpLocation.Z = curOwnerLocation.Z;
			extraLocation.Push(tmpLocation);
			extraRotation.Push((tmpLocation - curOwnerLocation).Rotation());

			tmpLocation = TargetLocation + Owner->GetActorRightVector() * 100 * index;
			tmpLocation.Z = curOwnerLocation.Z;
			extraLocation.Push(TargetLocation + Owner->GetActorRightVector() * 100 * index);
			extraRotation.Push((tmpLocation - curOwnerLocation).Rotation());
		}

		for (int32 index = 0; index < extraLocation.Num(); index++)
		{
			SpawnMagic(MagicKey, curOwnerLocation, extraLocation[index], extraRotation[index]);
		}
		break;
	case ESkillType::InPlace:
		break;
	case ESkillType::Coord:
		bIsCoord = true;

		for (int32 index = 1; index <= ElementTray[CAST(int32, ECastingElement::Light)] * 2; index++)
		{
			CoordLocations.Push(TargetLocation + Owner->GetActorForwardVector() * 200 * index);
		}
		break;
	}
}

AC_MagicSkill* UC_MagicDispenser::SpawnMagic(FString Key, FVector CasterLocation, FVector MouseLocation, FRotator Rot)
{
	return Cast<UC_GameInstance>(GetWorld()->GetGameInstance())->GetMagicManager()->OnFireMagic(Key, CasterLocation, MouseLocation, Rot);
}

void UC_MagicDispenser::CastMagic(TArray<ECastingElement> Elements, FVector TargetPosition)
{
	InitCasting();

	TargetLocation = TargetPosition;

	for (int32 index = 0; index < Elements.Num(); index++)
	{
		int32 elementNum = CAST(int32, Elements[index]);

		MagicKey += FString::FromInt(elementNum);

		switch (elementNum)
		{
		case 1:
			ElementTray[CAST(int32, ECastingElement::Fire)]++;
			break;
		case 2:
			ElementTray[CAST(int32, ECastingElement::Ice)]++;
			break;
		case 3:
			ElementTray[CAST(int32, ECastingElement::Light)]++;
			break;
		case 4:
			ElementTray[CAST(int32, ECastingElement::Dark)]++;
			break;
		}
	}

	SetMagicProperty();
}

void UC_MagicDispenser::Update(float DeltaTime)
{
	if (bIsCoord == false) return;

	CurFrame += DeltaTime;
	
	if (CoordInterval < CurFrame)
	{
		CurFrame -= CoordInterval;
		
		SpawnMagic(CoordMagicKey, FVector::ZeroVector, CoordLocations[0]);
		CoordLocations.RemoveAt(0);

		if (CoordLocations.Num() == 0)
		{
			bIsCoord = false;
			CoordLocations.Empty();
			CoordMagicKey = "";
		}
	}
}

//void UC_MagicDispenser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}