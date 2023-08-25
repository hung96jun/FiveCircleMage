#include "Characters/Monster/AIControllers/C_BossAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AC_BossAIController::AC_BossAIController()
{
	FString path;

	path = "/Script/AIModule.BehaviorTree'/Game/Blueprint/Characters/Enemy/Boss/BT_Boss.BT_Boss'";
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTOb(*path);

	if(BTOb.Succeeded())
		BTAsset = BTOb.Object;
}

void AC_BossAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AC_BossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_BossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	Character = Cast<AC_Boss>(InPawn);

	if (Character == nullptr) return;
	
	UBlackboardComponent* blackboard = nullptr;
	if (UseBlackboard(BTAsset->GetBlackboardAsset(), blackboard))
	{
		Blackboard = blackboard;
		Character->SetBehaviorTree(BTAsset, Blackboard);
		RunBehaviorTree(BTAsset);
	}
}

void AC_BossAIController::OnUnPossess()
{
}
