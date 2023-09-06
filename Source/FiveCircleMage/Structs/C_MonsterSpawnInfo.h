#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Weapons/Weapon/C_WeaponBase.h"
#include "C_MonsterSpawnInfo.generated.h"

/**
 * 
 */
//class USkeletalMesh;
//class UAnimInstance;
//class AAIController;
//class UBehaviorTree;

USTRUCT(BlueprintType)
struct FAttachWeaponInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	const FString GetBoneName() const { return BoneName; }
	TSubclassOf<AC_WeaponBase> GetWeaponClass() const { return WeaponClass; }
	const FName GetWeaponProfileName() const { return ProfileName; }
	const FVector GetBoxCollisionExtent() const { return Extent; }

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	FString WeaponName = L"";

	/**
	* BoneName to be attached first
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		FString BoneName = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TSubclassOf<AC_WeaponBase> WeaponClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoxCollision")
		FName ProfileName = "Weapon";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoxCollision")
		FVector Extent;
};


USTRUCT(BlueprintType)
struct FMonsterSpawnInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	const FString GetName() const { return Name; }
	const float GetMaxHP() const { return MaxHP; }
	const float GetMoveSpeed() const { return MoveSpeed; }
	const float GetCollisionHalfHeight() const { return HalfHeight; }
	const float GetCollisionRadius() const { return Radius; }
	USkeletalMesh* GetSkeletalMesh() const { return Mesh; }
	const float GetMeshScale() const { return MeshScale; }
	UAnimInstance* GetAnimInstance() const { return AnimInstance; }
	//AAIController* GetAIController() const { return AIController; }
	TSubclassOf<AAIController> GetAIControllerClass() { return AIController; }
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	TArray<FAttachWeaponInfo> GetWeaponInfos() const { return WeaponInfos; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name = L"";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MaxHP = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MoveSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		float HalfHeight = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		float Radius = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		USkeletalMesh* Mesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		float MeshScale = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		UAnimInstance* AnimInstance = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		TSubclassOf<AAIController> AIController = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TArray<FAttachWeaponInfo> WeaponInfos;
};

UCLASS()
class FIVECIRCLEMAGE_API UC_MonsterSpawnInfo : public UObject
{
	GENERATED_BODY()
	
public:
};
