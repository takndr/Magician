#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "CSkillQuickSlot.generated.h"

UCLASS()
class MAGICIAN_API UCSkillQuickSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UCSkillQuickSlot(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;

public:
	bool IsInSkillSlot();
	void DoAction();

protected:
	UFUNCTION(BlueprintCallable)
		void SetTickTimeline(float DeltaTime);

private:
	UFUNCTION()
		void CoolDown(float Output);

	UFUNCTION()
		void CoolDownComplete();

protected:
	UPROPERTY(EditAnywhere)
		FText KeyText;

private:
	UPROPERTY(meta = (BindWidget))
		class UCSkillIcon* Icon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* KeyName;

	UPROPERTY(meta = (BindWidget))
		class UImage* SkillCoolDown;

private:
	class UMaterialInstanceDynamic* CoolDownMaterial;

	class UCurveFloat* CoolDownCurve;
	FTimeline Timeline;
	FOnTimelineFloat OnTimeline;
	FOnTimelineEvent FinishTimeline;
};
