#include "Enemy/CAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"

#include "Global.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent(this, &Perception, "Perception");
	CHelpers::CreateActorComponent(this, &Behavior, "Behavior");

	SightPerception = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

	SightPerception->SightRadius = 1000.0f;
	SightPerception->LoseSightRadius = 1000.0f;
	SightPerception->PeripheralVisionAngleDegrees = 90.0f;
	SightPerception->SetMaxAge(2.0f);
	SightPerception->DetectionByAffiliation.bDetectEnemies = false;
	SightPerception->DetectionByAffiliation.bDetectFriendlies = false;
	SightPerception->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*SightPerception);
	Perception->SetDominantSense(SightPerception->GetClass());
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDebugMode);

	FVector center = PossessedEnemy->GetActorLocation();

	DrawDebugSphere(GetWorld(), center, SightPerception->SightRadius, 30, FColor::Green);
	DrawDebugSphere(GetWorld(), center, BehaviorRange, 30, FColor::Red);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemy = Cast<ACEnemy>(InPawn);

	UBehaviorTree* behaviorTree = PossessedEnemy->GetBehaviorTree();
	CheckNull(behaviorTree);

	UseBlackboard(behaviorTree->GetBlackboardAsset(), Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(behaviorTree);

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACPlayer* player = nullptr;
	for (const auto& actor : actors)
	{
		player = Cast<ACPlayer>(actor);
		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("PlayerKey", player);
}