#include "Components/C_MagicDispenser.h"
#include "Global.h"
#include "Math/UnrealMathUtility.h"
#include "C_GameInstance.h"
#include "Managers/C_MagicManager.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "Weapons/Magic/C_MagicInplace.h"
#include "Weapons/Magic/MesObjects/C_LivingBoom.h"

UC_MagicDispenser::UC_MagicDispenser()
{
	ElementTray.SetNum(5);
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
	bool isBasicMagic = ElementTray[CAST(int32, ECastingElement::Fire)] +
		ElementTray[CAST(int32, ECastingElement::Ice)] > 0;

	bool isEnchantedMagic = (ElementTray[CAST(int32, ECastingElement::Light)] + ElementTray[CAST(int32, ECastingElement::Dark)]) > 0;

	// Seperate Basic element and Enchanted element
	// Basic: fire || ice
	// Enchanted: light || dark
	if (isBasicMagic && isEnchantedMagic)
	{
		MagicKey = "";
		int iter;
		int elementNum;

		if (ElementTray[CAST(int32, ECastingElement::Fire)])
			elementNum = CAST(int32, ECastingElement::Fire);
		else
			elementNum = CAST(int32, ECastingElement::Ice);

		iter = ElementTray[CAST(int32, ECastingElement::Fire)] + ElementTray[CAST(int32, ECastingElement::Ice)];

		for (int32 i = 0; i < 5; i++)
		{
			if (iter)
			{
				MagicKey += FString::FromInt(elementNum);
				iter--;
			}
			else
				MagicKey += "0";
		}

		if (ElementTray[CAST(int32, ECastingElement::Light)] > 0)
		{
			SetMultiple();
		}
		else if (ElementTray[CAST(int32, ECastingElement::Dark)] > 0)
		{
			SetDarkness();
		}
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
		CoordMagicKey = MagicKey;

		for (int32 index = 1; index <= ElementTray[CAST(int32, ECastingElement::Light)] * 2; index++)
		{
			CoordLocations.Push(TargetLocation + Owner->GetActorForwardVector() * 600 * index);
		}
		break;
	case ESkillType::Mes:
		AC_LivingBoom* livingBoom = Cast<AC_LivingBoom>(curCastingMagicSkill);
		livingBoom->SetMultple(ElementTray[CAST(int32, ECastingElement::Light)]);
		break;
	}
}

void UC_MagicDispenser::SetDarkness()
{
	float tmpDamageFactor = 1.0f + (DarknessDamageFactor * ElementTray[CAST(int32, ECastingElement::Dark)]);

	AC_MagicSkill* curCastingMagicSkill = nullptr;
	curCastingMagicSkill = SpawnMagic(MagicKey, Owner->GetActorLocation(), TargetLocation, Owner->GetActorRotation(), true);

	curCastingMagicSkill->SetDamageFactor(tmpDamageFactor);
}

AC_MagicSkill* UC_MagicDispenser::SpawnMagic(FString Key, FVector CasterLocation, FVector MouseLocation, FRotator Rot, bool bIsDarkEnchanted)
{
	AC_MagicSkill* magicSkill = Cast<UC_GameInstance>(GetWorld()->GetGameInstance())->GetMagicManager()->OnFireMagic(Owner, Key, CasterLocation, MouseLocation, Rot);

	if (magicSkill == nullptr) return nullptr;
	magicSkill->InitDamageFactor();

	return magicSkill;
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
