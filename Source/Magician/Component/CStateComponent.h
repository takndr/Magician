#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Attack, Dodge, Dead, Wait
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICIAN_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCStateComponent();
protected:
	virtual void BeginPlay() override;
//===================================================================
public:
	FORCEINLINE bool IsIdle() { return State == EStateType::Idle; }
	FORCEINLINE bool IsAttack() { return State == EStateType::Attack; }
	FORCEINLINE bool IsDodge() { return State == EStateType::Dodge; }
	FORCEINLINE bool IsDead() { return State == EStateType::Dead; }
	FORCEINLINE bool IsWait() { return State == EStateType::Wait; }

	FORCEINLINE void SetIdle() { State = EStateType::Idle; }
	FORCEINLINE void SetAttack() { State = EStateType::Attack; }
	FORCEINLINE void SetDodge() { State = EStateType::Dodge; }
	FORCEINLINE void SetDead() { State = EStateType::Dead; }
	FORCEINLINE void SetWait() { State = EStateType::Wait; }
//===================================================================

//===================================================================
private:
	EStateType State;
		
};
