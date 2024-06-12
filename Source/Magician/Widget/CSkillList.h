#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSkillList.generated.h"

UCLASS()
class MAGICIAN_API UCSkillList : public UUserWidget
{
	GENERATED_BODY()
public:
	UCSkillList(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;
//=====================================================
public:
	void CreateSkillWidget(class UCSkillData* SkillData);
	void RefreshSkillWidget();

	void Attach();
	void Detach();
	bool IsOpened();
	void UpdateSkillPoint();

private:
//=====================================================
private:
	UFUNCTION()
		void OnCloseButtonDown();
//=====================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillPoint;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* ActiveScroll;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* PassiveScroll;

//=====================================================
private:
	TSubclassOf<class UCSkillWidget> SkillWidgetClass;
	TArray<class UCSkillWidget*> SkillWidgets;
	class ACharacter* OwningPlayer;
};
