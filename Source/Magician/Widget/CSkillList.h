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
	void Attach();
	void Detach();
	bool IsOpened();

private:
	void SettingSkillPoint();
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

	//UPROPERTY(meta = (BindWidget))
	//	class UUniformGridPanel* ActivePanel;

	//UPROPERTY(meta = (BindWidget))
	//	class UUniformGridPanel* PassivePanel;

//=====================================================
private:
	TSubclassOf<class UCSkillWidget> SkillWidgetClass;
	class ACharacter* OwningPlayer;
};
