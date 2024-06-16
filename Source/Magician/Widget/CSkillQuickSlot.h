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
	class UCSkillData* GetInSkillSlot();

	void OnSelected();
	void OffSelected();

protected:
	UFUNCTION(BlueprintCallable)
		void SetTickTimeline(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void BindCoolDown();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsSelected();

private:
	UFUNCTION()
		void DoAction();

	UFUNCTION()
		void CoolDown(float Output);

	UFUNCTION()
		void CoolDownComplete();

protected:
	UPROPERTY(EditAnywhere)
		FText KeyText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCSkillIcon* Icon;

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* KeyName;

	UPROPERTY(meta = (BindWidget))
		class UImage* SkillCoolDown;

	UPROPERTY(meta = (BindWidget))
		class UImage* SkillSelected;

private:
	class UMaterialInstanceDynamic* CoolDownMaterial;

	class UCurveFloat* CoolDownCurve;
	FTimeline Timeline;
	FOnTimelineFloat OnTimeline;
	FOnTimelineEvent FinishTimeline;
};
