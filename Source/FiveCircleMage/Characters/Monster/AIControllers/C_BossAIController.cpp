#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Monster/C_Boss.h"
#include "Characters/Player/C_Mage.h"

#include "Utilities/CLog.h"

AC_BossAIController::AC_BossAIController()
{
}

void AC_BossAIController::BeginPlay()
{
	Super::BeginPlay();

	AttackTimerDelegate.BindUFunction(this, L"EndAttacking");

	Target = Cast<AC_Mage>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Blackboard.Get()->SetValueAsObject(L"Target", Target);

	Character = Cast<AC_Boss>(GetCharacter());
	Character->SetTarget(Target);
}

void AC_BossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Blackboard != nullptr)
	{
		AC_Boss* boss = Cast<AC_Boss>(GetCharacter());
		if (boss == nullptr) return;

		AActor* otherActor = Cast<AActor>(Blackboard->GetValueAsObject("Target"));
		if (otherActor == nullptr) return;

		FVector location = otherActor->GetActorLocation();

		//boss->SetTargetLocation(location);
	}
}

void AC_BossAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
}

void AC_BossAIController::OnAttacking()
{
	bAttacking = true;
	Blackboard.Get()->SetValueAsBool(L"bAttacking", bAttacking);

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackCoolTime, false);
}

void AC_BossAIController::EndAttacking()
{
	bAttacking = false;
	Blackboard.Get()->SetValueAsBool(L"bAttacking", bAttacking);

	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void AC_BossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	Character = Cast<AC_Boss>(InPawn);
	if (Character->GetBehaviorTree() == nullptr) return;

	AttackCoolTime = Character->GetAttackCoolTime();

	UBlackboardComponent* blackboard = nullptr;
	if (UseBlackboard(Character->GetBehaviorTree()->GetBlackboardAsset(), blackboard))
		RunBehaviorTree(Character->GetBehaviorTree());

	Blackboard = blackboard;
	Blackboard.Get()->SetValueAsFloat(L"AttackRange", Character->GetAttackRange());
	Blackboard.Get()->SetValueAsFloat(L"Distance", 1000.0f);

}

void AC_BossAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
