#include "Characters/Monster/C_Monster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/Texture.h"
#include "NiagaraDataInterface.h"
#include "NiagaraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"

#include "UI/C_MonsterUI.h"
#include "Weapons/Weapon/C_WeaponBase.h"

#include "Utilities/CLog.h"

AC_Monster::AC_Monster()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"";
	{
		path = L"/Script/Niagara.NiagaraSystem'/Game/Assets/Particles/NS_DissolveEffect.NS_DissolveEffect'";
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> niagara(*path);

		if (niagara.Succeeded())
			DissolveInfo.DissolveEffect = niagara.Object;
	}

	{
		MonsterUI = CreateDefaultSubobject<UWidgetComponent>("UI");
		MonsterUI->SetupAttachment(RootComponent);

		path = L"UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/BpC_MonsterUI.BpC_MonsterUI_C'";
		path = L"UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/BpC_MonsterUI.BpC_MonsterUI_C'";
		ConstructorHelpers::FClassFinder<UC_MonsterUI> widgetClass(*path);
		if (widgetClass.Succeeded())
		{
			MonsterUI->SetWidgetSpace(EWidgetSpace::Screen);
			MonsterUI->SetWidgetClass(widgetClass.Class);
			MonsterUI->SetDrawSize(FVector2D(200.0f, 50.0f));

			MonsterUI->AddRelativeLocation(FVector(0.0f, 0.0f, 220.0f));
		}
	}
}

void AC_Monster::BeginPlay()
{
	Super::BeginPlay();

	GenericTeamID = 2;

	ForceType = EUnitForceType::Monster;

	HPBar = Cast<UC_MonsterUI>(MonsterUI->GetWidget());
	HPBar->Init();

	DissolveTimerDelegate.BindUFunction(this, L"DissolveUpdate");
	FinishTimerDelegate.BindUFunction(this, L"FinishDissolveEffect");
}

void AC_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector start, end, forward;
	//start = GetActorLocation();
	//forward = GetActorForwardVector();
	//end = start + (forward * 1000.0f);
	//end.Z = start.Z;
	//TArray<AActor*> ignores;
	//ignores.Add(this);
	//FHitResult hits;
	//bool bCheck = UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, 
	//	ETraceTypeQuery::TraceTypeQuery3, false, ignores, 
	//	EDrawDebugTrace::ForOneFrame, hits, true);

	//if (bCheck == true)
	//	
	// L"Trace Success", 0.01f, FColor::Red);
	//else
	//	CLog::Print(L"Trace Failed", 0.01f, FColor::Red);
}

void AC_Monster::SetAttackNum(const int Num)
{
	bAttacking = true;
	AttackNum = Num;
}

void AC_Monster::ResetAttackState()
{
	bAttacking = false;
	AttackNum = -1;

	CLog::Print(L"ResetAttackState", 10.0f, FColor::Cyan);
}

void AC_Monster::OnDeath()
{
	Super::OnDeath();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Weapon != nullptr)
	{
		Weapon->SetActive(false);
		Weapon = nullptr;
	}

	CLog::Print(L"Monster OnDissolveEffect", 10.0f, FColor::Purple);
	DissolveInfo.OnDissolveEffect(GetMesh(), this);

	GetWorld()->GetTimerManager().SetTimer(DissolveTimerHandle, DissolveTimerDelegate, 0.1f, true);
	GetWorld()->GetTimerManager().SetTimer(FinishTimerHandle, FinishTimerDelegate, 2.0f, false);
}

void AC_Monster::OnAttacking()
{
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear - Weapon is nullptr", 10.0f, FColor::Red);
		return;
	}
	else
		CLog::Print(L"Bear - Weapon is not nullptr", 10.0f, FColor::Blue);

	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AC_Monster::EndAttacking()
{
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear - Weapon is nullptr", 10.0f, FColor::Red);
		return;
	}
	else
		CLog::Print(L"Bear - Weapon is not nullptr", 10.0f, FColor::Blue);

	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AC_Monster::SetMonsterInfo(FMonsterInformation Info)
{
	UnitStatus = FUnitStatus(Info.GetMaxHP(), Info.GetMoveSpeed());
	AttackRange = Info.GetAttackRange();
	AttackCoolTime = Info.GetAttackCoolTime();
	GetMesh()->AnimClass = Info.GetAnimInstanceClass();
	if (Info.GetSkeletalMesh() != nullptr)
	{
		GetMesh()->SetSkeletalMesh(Info.GetSkeletalMesh());
		GetMesh()->SetRelativeScale3D(FVector(Info.GetMeshScale()));

		GetMesh()->SetRelativeLocation(FVector(Info.GetMeshLocalLocation()));
		GetMesh()->SetRelativeRotation(FRotator(Info.GetMeshLocalRotation()));
	}
	else
	{
		CLog::Print(L"Error : Monster class - SetMonsterInfo function, Info parameter GetSkeletalMesh() return value is nullptr", 1000.0f, FColor::Red);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(Info.GetCollisionHalfHeight());
	GetCapsuleComponent()->SetCapsuleRadius(Info.GetCollisionRadius());
	BehaviorTree = Info.GetBehaviorTree();
	DissolveInfo = Info.GetDissolveInfo();

	GetMesh()->GetAnimInstance()->NativeBeginPlay();
}

void AC_Monster::GetDmg(const float Dmg, const EUnitState Type)
{
	Super::GetDmg(Dmg, Type);

	HPBar->SetHealth(UnitStatus.GetHPRate());
}

void AC_Monster::AttachWeapon(AC_WeaponBase* Actor, const FName BoneName, const FVector Extent, const FVector Offset)
{
	Weapon = Actor;
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear Object - Weapon is nullptr", 100.0f, FColor::Red);
		return;
	}

	Weapon->SetBoxExtent(Extent);
	Weapon->SetActorRelativeLocation(Offset);
}

void AC_Monster::AttachWeapon(const FName BoneName, const FVector Offset)
{
	if (Weapon == nullptr) return;

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	if (Weapon == nullptr)
	{
		CLog::Print(L"Bear Object - Weapon is nullptr", 100.0f, FColor::Red);
		return;
	}

	Weapon->SetActorRelativeLocation(Offset);
}

void AC_Monster::DissolveUpdate()
{
	if (DissolveInfo.DissolveComp == nullptr) return;

	// Max / (Time / Interval)
	float value = 1.0f / (2.0f / 0.1f);
	DissolveInfo.Amount -= FMath::Lerp(1.0f, -0.1, value);

	DissolveInfo.DissolveComp->SetNiagaraVariableFloat(L"Amount", DissolveInfo.Amount);
}

void AC_Monster::FinishDissolveEffect()
{
	GetWorld()->GetTimerManager().ClearTimer(DissolveTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FinishTimerHandle);
}
