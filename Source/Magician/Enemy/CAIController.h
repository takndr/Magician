#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class MAGICIAN_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
// ==================================================================
public:
	FORCEINLINE class ACEnemy* GetPossessedEnemy() { return PossessedEnemy; }
// ==================================================================
private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
// ==================================================================
private:
	class ACEnemy* PossessedEnemy;
	class UAISenseConfig_Sight* SightPerception;
// ==================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;

	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.0f;

	UPROPERTY(EditAnywhere)
		bool bDebugMode = true;
};
