// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Magic/C_MagicSkill.h"
#include "Weapons/Magic/C_MesObject.h"
#include "C_MagicSpawn.generated.h"

/**
 * 
 */
UCLASS()
class FIVECIRCLEMAGE_API AC_MagicSpawn : public AC_MagicSkill
{
	GENERATED_BODY()
	
public:
	AC_MagicSpawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void BeginCasting(FVector CasterPosition, FVector TargetPosition, FRotator Rotation = FRotator::ZeroRotator) override;

	void SetSpawnObject(AC_MesObject* Object) { SpawnObject = Object; }

protected:
	AC_MesObject* SpawnObject;
};
