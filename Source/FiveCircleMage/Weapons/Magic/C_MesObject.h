// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MesObject.generated.h"

UCLASS()
class FIVECIRCLEMAGE_API AC_MesObject : public AActor
{
	GENERATED_BODY()
	
public:
	AC_MesObject();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Spawn(FVector SpawnLocation) {}

};
