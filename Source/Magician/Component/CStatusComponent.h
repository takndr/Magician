#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHpChangedSignature, float, InPercent, float, InMax, float, InCurrent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICIAN_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCStatusComponent();
protected:
	virtual void BeginPlay() override;
// =================================================================
public:
	FORCEINLINE bool IsDead() { return CurrentHp <= 0; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetHpRatio() { return CurrentHp / MaxHp; }
	FORCEINLINE float GetMoveSpeed() { return MoveSpeed; }
// =================================================================
public:
	UFUNCTION(BlueprintCallable)
		void IncreaseHealth(float Dx);

	UFUNCTION(BlueprintCallable)
		void DecreaseHealth(float Dx);
// =================================================================
public:
	FHpChangedSignature OnHpChanged;

protected:
	class ACharacter* OwnerCharacter;
	float CurrentHp;
// =================================================================
protected:
	UPROPERTY(EditAnywhere, Category = "Status : Hp")
		float MaxHp = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Moving")
		float MoveSpeed = 600.0f;
};
