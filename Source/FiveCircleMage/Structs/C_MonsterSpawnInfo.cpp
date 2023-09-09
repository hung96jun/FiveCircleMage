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
	//Width = 0.1f;
	DissolveComp->SetNiagaraVariableFloat(L"Amount", 1.0f);
	DissolveComp->SetNiagaraVariableFloat(L"Width", Width);
}

void FDissolveInfo::OnDissolveEffect(USkeletalMeshComponent* Skel, AActor* Target)
{
	if (Skel == nullptr) return;
	CLog::Print(L"Skel is not nullptr - DissolveInfo", 1.0f, FColor::Cyan);
	if (Target == nullptr) return;
	CLog::Print(L"Target is not nullptr - DissolveInfo", 1.0f, FColor::Cyan);

	CLog::Print(L"OnDissolveEffect - DissolveInfo", 1.0f, FColor::Cyan);

	UMaterialInterface* mat = Skel->GetMaterial(0);
	if (mat == nullptr) return;
	
	//DynamicMat = UMaterialInstanceDynamic::Create(mat, Target);
	DynamicMat = Skel->CreateDynamicMaterialInstance(0, mat);
	if (DynamicMat == nullptr)
	{
		CLog::Print(L"DissolveInfo - DynamicMat is nullptr", 10.0f, FColor::Red);
		return;
	}

	if (NoiseTexture == nullptr)
	{
		CLog::Print(L"DissolveInfo - DynamicMat is nullptr", 10.0f, FColor::Red);
		return;
	}
	DynamicMat->SetTextureParameterValue(L"NoiseTexture", NoiseTexture);

	DissolveComp = UNiagaraFunctionLibrary::SpawnSystemAttached(DissolveEffect, Target->GetRootComponent(), L"None",
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);

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
