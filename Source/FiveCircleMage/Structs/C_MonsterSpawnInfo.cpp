#include "Structs/C_MonsterSpawnInfo.h"

#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"

#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Weapons/Weapon/C_WeaponBase.h"

#include "Utilities/CLog.h"

void FDissolveInfo::InitInfo()
{
	if (DissolveComp == nullptr)
		return;

	Amount = 1.0f;
	Width = 0.1f;
	DissolveComp->SetNiagaraVariableFloat(L"Amount", 1.0f);
	DissolveComp->SetNiagaraVariableFloat(L"Width", 0.1f);
}

void FDissolveInfo::OnDissolveEffect(USkeletalMeshComponent* Skel, UObject* Target)
{
	if (Skel == nullptr) return;
	if (Target == nullptr) return;

	UMaterialInterface* mat = Skel->GetMaterial(0);
	if (mat == nullptr) return;

	DynamicMat = UMaterialInstanceDynamic::Create(mat, Target);
	if (DynamicMat == nullptr) return;

	if (NoiseTexture == nullptr) return;
	DynamicMat->SetTextureParameterValue(L"NoiseTexture", NoiseTexture);

	UNiagaraFunctionLibrary::SetTextureObject(DissolveComp, L"NoiseTexture", NoiseTexture);
}

//void FDissolveInfo::OnDissolveEffect(USkeletalMeshComponent* Skel, UObject* Target)
//{
//	if (Target == nullptr) return;
//	if (Skel == nullptr) return;
//
//	CLog::Print(L"OnDissolveEffect", 5.0f, FColor::Green);
//
//	// Effect Setting
//	{
//		DissolveComp = UNiagaraFunctionLibrary::SpawnSystemAttached(DissolveEffect, Skel, L"Root",
//			FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
//
//		if (DissolveComp == nullptr) return;
//	
//		DissolveComp->SetNiagaraVariableFloat(L"Amount", 1.0f);
//		DissolveComp->SetNiagaraVariableFloat(L"Width", 0.1f);
//		DissolveComp->SetVariableTexture(L"TextureSample", NoiseTexture);
//		UNiagaraFunctionLibrary::OverrideSystemUserVariableSkeletalMeshComponent(DissolveComp, L"SkeletalMesh", Skel);
//
//		UMaterialInstance* material = Cast<UMaterialInstance>(Skel->GetMaterial(0));
//		if (material == nullptr) return;
//
//		DynamicMat = UMaterialInstanceDynamic::Create(Skel->GetMaterial(0), Target);
//		if (DynamicMat == nullptr) return;
//
//		DynamicMat->SetScalarParameterValue(L"Amount", Amount);
//		//Amount = 0.0f;
//	}
//	CLog::Print(L"Finish OnDissolveEffect", 5.0f, FColor::Yellow);
//}
