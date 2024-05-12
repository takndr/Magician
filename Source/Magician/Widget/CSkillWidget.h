#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSkillWidget.generated.h"

UCLASS()
class MAGICIAN_API UCSkillWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		void OnSkillUpButtonDown();

	UFUNCTION()
		void OnSkillDownButtonDown();

public:
	void SetSkillWidget(class UCSkillData* SkillData);

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxLevel;

	UPROPERTY(meta = (BindWidget))
		class UCSkillIcon* Icon;

	UPROPERTY(meta = (BindWidget))
		class UButton* SkillUpButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* SkillDownButton;

protected:
	UPROPERTY(EditAnywhere)
		class UCSkillData* Data;
};
