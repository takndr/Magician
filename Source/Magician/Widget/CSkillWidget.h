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
// ========================================================
private:
	UFUNCTION()
		void OnSkillUpButtonDown();

	UFUNCTION()
		void OnSkillDownButtonDown();

public:
	void SetSkillWidget(class UCSkillData* SkillData, class UCSkillList* ListWidget = nullptr);
	void RefreshWidget();

private:
	void UpdateCurrentLevel();
	void UpdateMaxLevel();

// ========================================================
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UCSkillIcon* Icon;

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillType;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillName;

	UPROPERTY(meta = (BindWidget))
		class UButton* SkillUpButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* SkillDownButton;
// ========================================================
protected:


// ========================================================
private:
	class UCSkillData* Data;
	class ACharacter* OwningPlayer;
	class UCSkillComponent* SkillComp;
	class UCSkillList* SkillListWidget;
};
