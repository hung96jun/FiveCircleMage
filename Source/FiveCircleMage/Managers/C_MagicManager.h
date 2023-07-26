#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Enums/C_UnitType.h"
#include "Enums/C_SkillType.h"
#include "C_MagicManager.generated.h"

class UNiagaraSystem;
class AC_MagicSkill;


USTRUCT(BlueprintType)
struct FMagicPoolingInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FMagicPoolingInfo() {}
	FMagicPoolingInfo(const FString Key, TSubclassOf<AC_MagicSkill> Class, const ESkillType Type)
		: Key(Key), Class(Class), MagicType(Type) {}

	const FString& GetKey() { return Key; }
	const ESkillType& GetMagicType() { return MagicType; }
	//const int32& GetMax() { return Max; }
	TSubclassOf<AC_MagicSkill> GetClass() { return Class; }

	FMagicPoolingInfo& operator=(FMagicPoolingInfo* Other)
	{
		this->Key = Other->GetKey();
		this->Class = Other->GetClass();
		this->MagicType = Other->GetMagicType();
		//this->Max = Other->GetMax();

		return *this;
	}

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Key = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AC_MagicSkill> Class = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ESkillType MagicType = ESkillType::None;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	int32 Max = 0;
};

USTRUCT(BlueprintType)
struct FMagicInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FMagicInfo() {}

	const FString& GetMagicName() { return MagicName; }
	const ESkillType& GetMagicType() { return MagicType; }
	const FString& GetMainParticlePath() {return MainParticlePath; }
	const FString& GetEndParticlePath() {return EndParticlePath; }
	const float& GetMaxDuration() {return MaxDuration; }
	const float& GetMoveSpeed() {return MoveSpeed; }
	const float& GetDamage() {return Damage; }
	const EUnitState& GetDebuffType() {return DebuffType; }
	const float& GetCollisionHeight() {return CollisionHeight; }
	const float& GetCollisionRadius() {return CollisionRadius; }
	const FVector& GetCollisionScale() { return CollisionScale; }
	const FRotator& GetRotation() {return Rotation;}
	const TArray<float>& GetTemp() { return Temps; }

	void SetMainParticle(UNiagaraSystem* Particle) { MainParticle = Particle; }
	void SetEndParticle(UNiagaraSystem* Particle) { EndParticle = Particle; }

	UNiagaraSystem* GetMainParticle() { return MainParticle; }
	UNiagaraSystem* GetEndParticle() { return EndParticle; }

	FMagicInfo& operator=(FMagicInfo* Other)
	{
		this->MagicName = Other->GetMagicName();
		this->MagicType = Other->GetMagicType();
		this->MainParticlePath = Other->GetMainParticlePath();
		this->EndParticlePath = Other->GetEndParticlePath();
		this->MaxDuration = Other->GetMaxDuration();
		this->MoveSpeed = Other->GetMoveSpeed();
		this->Damage = Other->GetDamage();
		this->DebuffType = Other->GetDebuffType();
		this->CollisionHeight = Other->GetCollisionHeight();
		this->CollisionRadius = Other->GetCollisionRadius();
		this->CollisionScale = Other->GetCollisionScale();
		this->Rotation = Other->GetRotation();
		this->Temps = Other->GetTemp();

		return *this;
	}

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FString MagicName = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		ESkillType MagicType = ESkillType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FString MainParticlePath = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FString EndParticlePath = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MaxDuration = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MoveSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float Damage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		EUnitState DebuffType = EUnitState::Normal;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		float CollisionHeight = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		float CollisionRadius = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		FVector CollisionScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		FRotator Rotation = FRotator::ZeroRotator;

	/**
	Enter the parameter values to be used for the function in temp in order.
	1. Missile
		- Nothing
	
	2. Coord
		- SetDelayTime(Delay time for damaging)
		(FirePillar, Meteor)
	
	3. Spawn
		- Nothing
	
	4. Inplace
		- void SetMaxRadius(Radius of capsule collision)
		- void SetSpreadSpeed(speed of increasing collision radius)
		(FlashBang, FrostNova)
	
	5. Beam
		- Nothing
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Additional Information")
		TArray<float> Temps;

private:
	UNiagaraSystem* MainParticle = nullptr;
	UNiagaraSystem* EndParticle = nullptr;
};

UCLASS()
class FIVECIRCLEMAGE_API AC_MagicManager : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, FMagicPoolingInfo> PoolingInfos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, FMagicInfo> MagicInfos;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxMagic = 10;

public:	
	AC_MagicManager();

	//template<typename T>
	//T* OnFireMagic(const FString Key, const ESkillType Type, const FVector Location);

	///////////////////////////////////////////////////////////////////////////
	//Based on the MagicInfo information entered in the DataTable Blueprint, 
	//the pooled MagicSkill object is called and fired using the Key value 
	//and Type value entered as parameters.
	//@param Key : Magic key value
	//@return Returns the called object among the pooled objects
	//@return Returns nullptr if there is no pooled object
	///////////////////////////////////////////////////////////////////////////
	AC_MagicSkill* OnFireMagic(const FString Key, const FVector CasterLocation, const FVector TargetLocation, const FRotator Rotation = FRotator::ZeroRotator);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void CreateMagicObject(TPair<FString, FMagicPoolingInfo> Info);

private:
	UDataTable* PoolingDataTable;
	UDataTable* MagicDataTable;

	TMap<FString, TArray<AC_MagicSkill*>> Magics;
	TMap<FString, uint16> MagicCount;
};