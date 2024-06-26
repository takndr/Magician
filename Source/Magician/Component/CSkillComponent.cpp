#include "Component/CSkillComponent.h"

#include "Player/CPlayer.h"
#include "Widget/CMainWidget.h"
#include "Widget/CSkillList.h"

#include "Skill/CSkillData.h"

#include "Global.h"

UCSkillComponent::UCSkillComponent()
{

}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	ACPlayer* ownerCharacter = Cast<ACPlayer>(GetOwner());

	// 플레이어의 skill list widget을 가져오고
	UCMainWidget* mainWidget = ownerCharacter->GetSkillHUDWidget();

	// TArray<SkillData> Skills의 배열을 돌면서 skill list widget에 추가
	for (auto skill : Skills)
	{
		skill->BeginPlay(ownerCharacter);
		mainWidget->SetSkillList(skill);
	}
}

void UCSkillComponent::UpgradeSkill(class UCSkillData* Skill)
{
	CheckFalse((SkillPoints > 0));
	CheckTrue((Skill->CurrentLevel == Skill->MaxLevel));
	CheckFalse((Skill->CanLearnedSkill()));

	// SkillData 관련 업데이트
	Skill->Upgrade();
	DecreaseSkillPoints(1);

	// 전체 스킬 리프레쉬
	for (auto skill : Skills)
	{
		skill->RefreshSkill();
	}

	// SkillWidgets 리프레쉬
	ACPlayer* ownerCharacter = Cast<ACPlayer>(GetOwner());
	UCMainWidget* mainWidget = ownerCharacter->GetSkillHUDWidget();
	UCSkillList* skillList = mainWidget->GetSkillList();
	skillList->RefreshSkillWidget();
}

void UCSkillComponent::DowngradeSkill(class UCSkillData* Skill)
{
	CheckTrue((Skill->CurrentLevel == 0));

	// SkillData 관련 업데이트
	Skill->Downgrade();
	IncreaseSkillPoints(1);

	// 전체 스킬 리프레쉬
	for (auto skill : Skills)
	{
		skill->RefreshSkill();
	}

	// SkillWidgets 리프레쉬
	ACPlayer* ownerCharacter = Cast<ACPlayer>(GetOwner());
	UCMainWidget* mainWidget = ownerCharacter->GetSkillHUDWidget();
	UCSkillList* skillList = mainWidget->GetSkillList();
	skillList->RefreshSkillWidget();
}

void UCSkillComponent::IncreaseSkillPoints(int Point)
{
	SkillPoints += Point;
}

void UCSkillComponent::DecreaseSkillPoints(int Point)
{
	SkillPoints -= Point;
}