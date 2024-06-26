#pragma once

#include "CoreMinimal.h"
#include "Component/CStatusComponent.h"
#include "CPlayerStatusComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FMpChangedSignature, float, InPercent);

UCLASS()
class MAGICIAN_API UCPlayerStatusComponent : public UCStatusComponent
{
	GENERATED_BODY()
public:
	UCPlayerStatusComponent();
protected:
	virtual void BeginPlay() override;
// =================================================================
public:
	UFUNCTION(BlueprintCallable)
		void IncreaseMana(float Dx);

	UFUNCTION(BlueprintCallable)
		void DecreaseMana(float Dx);

private:
	UFUNCTION()
		void RegenMana();
// =================================================================
public:
	FMpChangedSignature OnMpChanged;

private:
	float CurrentMp;
	float Level = 1;

	float MaxXp;
	float CurrentXp;

// =================================================================
protected:
	UPROPERTY(EditAnywhere, Category = "Status : Mp")
		float MaxMp = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Status : Mp")
		float MpRegen = 2.0f;
};

// ¸¶³ª ¸®Á¨