#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "C_MonsterSpawnInfo.generated.h"

/**
 * 
 */
class UNiagaraSystem;
class UNiagaraComponent;
class UMaterialInstanceDynamic;
class USkeletalMesh;
class UAnimInstance;
class UBehaviorTree;
class UTexture;
class AAIController;

class AC_WeaponBase;

USTRUCT(BlueprintType)
struct FAttachWeaponInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	const FString GetName() const { return WeaponName; }
	const FName GetBoneName() const { return BoneName; }
	TSubclassOf<AC_WeaponBase> GetWeaponClass() const { return WeaponClass; }
	const FName GetWeaponProfileName() const { return ProfileName; }
	const FVector GetBoxCollisionExtent() const { return Extent; }
	const FVector GetWeaponOffset() const { return Offset; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString WeaponName = L"";

	/**
	* BoneName to be attached first
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		FName BoneName = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TSubclassOf<AC_WeaponBase> WeaponClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoxCollision")
		FName ProfileName = "Weapon";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoxCollision")
		FVector Extent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoxCollision")
		FVector Offset;
};

USTRUCT(BlueprintType)
struct FMonsterPoolingInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	const FString GetTriggerName() const { return TriggerName; }
	const FString GetName() const { return MonsterName; }
	const TArray<FVector> GetLocations() const { return Locations; }
	const TArray<FRotator> GetRotations() const { return Rotations; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString TriggerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString MonsterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FVector> Locations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FRotator> Rotations;
};

USTRUCT(BlueprintType)
struct FDissolveInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FDissolveInfo() {}
	FDissolveInfo(UNiagaraSystem* DissolveEffect, float Amount, float Widgth, UTexture* NoiseTexture)
		: DissolveEffect(DissolveEffect), Amount(Amount), Width(Width), NoiseTexture(NoiseTexture) {}

	void InitInfo();
	void OnDissolveEffect(USkeletalMeshComponent* Skel, UObject* Target);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraSystem* DissolveEffect = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UNiagaraComponent* DissolveComp = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Width = 0.1f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture* NoiseTexture = nullptr;

	//UPROPERTY(BlueprintReadOnly)
	float Amount = 1.0f;

	//UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* DynamicMat = nullptr;
};

USTRUCT(BlueprintType)
struct FMonsterInformation : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	const FString GetName() const { return Name; }
	const float GetMaxHP() const { return MaxHP; }
	const float GetMoveSpeed() const { return MoveSpeed; }
	const float GetAttackRange() const { return AttackRange; }
	const float GetAttackCoolTime() const { return AttackCoolTime; }
	const float GetCollisionHalfHeight() const { return HalfHeight; }
	const float GetCollisionRadius() const { return Radius; }
	USkeletalMesh* GetSkeletalMesh() const { return Mesh; }
	const float GetMeshScale() const { return MeshScale; }
	TSubclassOf<UAnimInstance> GetAnimInstanceClass() const { return AnimInstance; }
	const FVector GetMeshLocalLocation() const { return LocalLocation; }
	const FRotator GetMeshLocalRotation() const { return LocalRotation; }
	TSubclassOf<AAIController> GetAIControllerClass() { return AIController; }
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	TArray<FAttachWeaponInfo> GetWeaponInfos() const { return WeaponInfos; }
	FDissolveInfo GetDissolveInfo() const { return DissolveInfo; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MaxHP = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MoveSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackRange = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackCoolTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		float HalfHeight = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		float Radius = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		USkeletalMesh* Mesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		float MeshScale = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		TSubclassOf<UAnimInstance> AnimInstance = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		FVector LocalLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		FRotator LocalRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		TSubclassOf<AAIController> AIController = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TArray<FAttachWeaponInfo> WeaponInfos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DissolveEffect")
		FDissolveInfo DissolveInfo;
};

UCLASS()
class FIVECIRCLEMAGE_API UC_MonsterSpawnInfo : public UObject
{
	GENERATED_BODY()
	
public:
};
