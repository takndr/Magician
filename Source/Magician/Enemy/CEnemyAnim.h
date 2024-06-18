#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CEnemyAnim.generated.h"

UCLASS()
class MAGICIAN_API UCEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bFalling = false;

private:
	class ACharacter* OwnerCharacter;
	class UCWeaponComponent* WeaponComponent;
};
