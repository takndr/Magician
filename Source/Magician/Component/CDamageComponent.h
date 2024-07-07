#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDamageComponent.generated.h"

UENUM(BlueprintType)
enum class EStatusEffect : uint8
{
	None, Burned, Frozen
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICIAN_API UCDamageComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCDamageComponent();
protected:
	virtual void BeginPlay() override;
// ========================================================
protected:
	UFUNCTION(BlueprintCallable)
		void TriggerEffect(EStatusEffect effect, class AController* Instigator);

// ========================================================
private:
	void BurnedEffect();
	void FrozenEffect();
// ========================================================
private:
	TMap<EStatusEffect, TSubclassOf<class ACSkillEffector>> Effector;
	class ACharacter* OwnerCharacter;


};
