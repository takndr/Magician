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

	void CastingStart();
	void CastingEnd();

private:
	void SelectSkill(class UCSkillQuickSlot* SkillSlot);
	void OffAllSkill();

public:
	UFUNCTION()
		void UpdateHpBar(float ratio, float Max, float Current);

	UFUNCTION()
		void UpdateMpBar(float ratio, float Max, float Current);

	UFUNCTION()
		void UpdateXpBar(float ratio, float Max, float Current);

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

	UPROPERTY(meta = (BindWidget))
		class UCStatBar* HpStatBar;

	UPROPERTY(meta = (BindWidget))
		class UCStatBar* MpStatBar;

	//UPROPERTY(meta = (BindWidget))
	//	class UProgressBar* Xp_bar;

	UPROPERTY(meta = (BindWidget))
		class UCCastingBar* CastingBar;

private:
	class ACPlayer* OwningPlayer;
};
