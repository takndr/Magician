#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

UCLASS()
class MAGICIAN_API ACEnemy : public ACharacter
{
	GENERATED_BODY()
public:
	ACEnemy();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
// =================================================================
public:
	FORCEINLINE FText GetEnemyName() { return EnemyName; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }
	FORCEINLINE bool IsHitNormal() { return bHitNormal; }
	FORCEINLINE bool IsHitKnockBack() { return bHitKnockBack; }
// =================================================================
protected:

// =================================================================
protected:
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue = 0.0f;

	bool bHitNormal = false;
	bool bHitKnockBack = false;

private:
	TArray<class ACharacter*> HittedCharacters;
// =================================================================
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComp;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Names")
		FText EnemyName;
// =================================================================
private:
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* SkillMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* DieMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* KnockbackMontage;
};
