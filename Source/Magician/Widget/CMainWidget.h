#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainWidget.generated.h"

UCLASS()
class MAGICIAN_API UCMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	void ControlSkillListWidget();
	void SetSkillList(class UCSkillData* SkillData);
	class UCSkillList* GetSkillList();

private:
	void SelectSkill(class UCSkillQuickSlot* SkillSlot);
	void OffAllSkill();

private:
	UFUNCTION()
		void DoSkill1();

	UFUNCTION()
		void DoSkill2();

	UFUNCTION()
		void DoSkill3();

	UFUNCTION()
		void DoSkill4();

	UFUNCTION()
		void DoSkill5();

private:
	UPROPERTY(meta = (BindWidget))
		class UCSkillQuickSlot* Skill1;

	UPROPERTY(meta = (BindWidget))
		class UCSkillQuickSlot* Skill2;

	UPROPERTY(meta = (BindWidget))
		class UCSkillQuickSlot* Skill3;

	UPROPERTY(meta = (BindWidget))
		class UCSkillQuickSlot* Skill4;

	UPROPERTY(meta = (BindWidget))
		class UCSkillQuickSlot* Skill5;

	UPROPERTY(meta = (BindWidget))
		class UCSkillList* SkillList;

private:
	class ACPlayer* OwningPlayer;
};
