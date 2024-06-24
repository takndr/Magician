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
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
// ========================================================
protected:
	UFUNCTION(BlueprintCallable)
		void TriggerEffect(EStatusEffect effect);

// ========================================================
private:
	void BurnedEffect();
	void FrozenEffect();
// ========================================================
private:
	TMap<EStatusEffect, TSubclassOf<class ACSkillEffector>> Effector;
};
