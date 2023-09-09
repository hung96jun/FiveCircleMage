// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Utilities/CLog.h"
#include "C_ParticleInfo.generated.h"

class UCapsuleComponent;

USTRUCT(BlueprintType)
struct FParticleInfo
{
	GENERATED_BODY()

public:
	void SetParticle(UNiagaraSystem* _Particle, FVector _Location, FRotator _Rotation)
	{
		Particle = _Particle;
		Location = _Location;
		Rotation = _Rotation;
	}

	void Play(UCapsuleComponent* Collision)
	{
		if (Particle == nullptr)
		{
			CLog::Print("Particle is nullptr!!!");
			return;
		}

		if (Collision == nullptr)
		{
			CLog::Print("Collision is nullptr!!");
			return;
		}

		Comp = UNiagaraFunctionLibrary::SpawnSystemAttached(Particle, Collision, L"None", Location, Rotation,
			EAttachLocation::KeepRelativeOffset, true);
		Comp->ResetSystem();
		Comp->SetVisibility(true);
	}

	void Stop()
	{
		Comp->SetPaused(true);
		Comp->SetVisibility(false);
	}

	void SetParticleScale(float Factor)
	{
		Comp->SetRelativeScale3D(FVector(Factor, Factor, Factor));
	}

	void SetParticleScale(float X, float Y, float Z)
	{
		Comp->SetRelativeScale3D(FVector(X, Y, Z));
	}

	void SetLocation(FVector Position)
	{
		Location = Position;
	}

	const bool IsActive() { return Particle != nullptr; }
	UNiagaraComponent*& GetComp() { return Comp; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraComponent* Comp = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraSystem* Particle = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Location = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FRotator Rotation = FRotator::ZeroRotator;
};

UCLASS()
class FIVECIRCLEMAGE_API UC_ParticleInfo : public UObject
{
	GENERATED_BODY()
	
};
