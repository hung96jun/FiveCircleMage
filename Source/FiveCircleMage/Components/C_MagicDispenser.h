// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include "Components/ActorComponent.h"
#include "Characters/Player/C_Mage.h"
#include "Enums/C_CastingElement.h"
#include "Enums/C_SkillType.h"
#include "C_MagicDispenser.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIVECIRCLEMAGE_API UC_MagicDispenser : public UActorComponent
{
	GENERATED_BODY()

public:
	UC_MagicDispenser();

	void SetOwner(AC_Mage* Mage) { Owner = Mage; }
	void CastMagic(TArray<ECastingElement> Elements, FVector TargetPosition);

	void Update(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SetSkills() {}

	void InitCasting();
	void SetMagicProperty();

	void SetMultiple();
	void SetDarkness() {}

private:
	AC_Mage* Owner;
	TArray<int32> ElementTray;

	FString MagicKey;
	FVector TargetLocation;
	map<FString, FString> Skills;

	bool bIsCoord = false;
	FString CoordMagicKey;
	const float CoordInterval = 1.0f;
	TArray<FVector> CoordLocations;

	float CurFrame = 0.0f;
}; 