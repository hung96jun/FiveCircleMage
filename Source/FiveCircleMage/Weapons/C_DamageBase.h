#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/C_DamageComponent.h"
#include "Characters/C_Unit.h"
#include "C_DamageBase.generated.h"

class UC_DamageComponent;

USTRUCT(BlueprintType)
struct FMagicInformation
{
	GENERATED_USTRUCT_BODY()

protected:

};

UCLASS()
class FIVECIRCLEMAGE_API AC_DamageBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UC_DamageComponent* DamageComp = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		EUnitState DebuffType = EUnitState::Normal;

public:
	AC_DamageBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetCollisionEnabled(ECollisionEnabled::Type Type) {}

	virtual void SetActive(const bool Value) { bActive = Value; }
	const bool IsActive() { return bActive; }

	void SetOwnerActor(AC_Unit* Actor) { OwnerActor = Actor; }

	void SetDamage(const float Value) { Damage = Value; }
	void SetDebuffType(const EUnitState Type) { DebuffType = Type; }

	void SetDamageFactor(float DamageFactor) { ExtraDamageFactor = DamageFactor; Damage *= ExtraDamageFactor; }
	void InitDamageFactor() { Damage /= ExtraDamageFactor; ExtraDamageFactor = 1.0f; }

	const FGenericTeamId GetTeamID() const { return OwnerActor->GetGenericTeamId(); }

protected:
	void Spawn(const FVector Location, const FRotator Rotation = FRotator::ZeroRotator) {}

protected:
	bool bActive = false;
	AC_Unit* OwnerActor = nullptr;
	float ExtraDamageFactor = 1.0f;
	float Damage = 0.0f;
};
