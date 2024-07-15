#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "CCastingBar.generated.h"

UCLASS()
class MAGICIAN_API UCCastingBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UCCastingBar(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;

public:
	void Attach();
	void Detach();

protected:
	UFUNCTION(BlueprintCallable)
		void SetTickTimeline(float DeltaTime);

private:
	UFUNCTION()
		void Casting(float Output);

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* CastingBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CastingText;

private:
	class UCurveFloat* CoolDownCurve;
	FTimeline Timeline;
	FOnTimelineFloat OnTimeline;
	FOnTimelineEvent FinishTimeline;
};
