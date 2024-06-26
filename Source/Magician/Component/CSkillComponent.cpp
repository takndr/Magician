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

	// �÷��̾��� skill list widget�� ��������
	UCMainWidget* mainWidget = ownerCharacter->GetSkillHUDWidget();

	// TArray<SkillData> Skills�� �迭�� ���鼭 skill list widget�� �߰�
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

	// SkillData ���� ������Ʈ
	Skill->Upgrade();
	DecreaseSkillPoints(1);

	// ��ü ��ų ��������
	for (auto skill : Skills)
	{
		skill->RefreshSkill();
	}

	// SkillWidgets ��������
	ACPlayer* ownerCharacter = Cast<ACPlayer>(GetOwner());
	UCMainWidget* mainWidget = ownerCharacter->GetSkillHUDWidget();
	UCSkillList* skillList = mainWidget->GetSkillList();
	skillList->RefreshSkillWidget();
}

void UCSkillComponent::DowngradeSkill(class UCSkillData* Skill)
{
	CheckTrue((Skill->CurrentLevel == 0));

	// SkillData ���� ������Ʈ
	Skill->Downgrade();
	IncreaseSkillPoints(1);

	// ��ü ��ų ��������
	for (auto skill : Skills)
	{
		skill->RefreshSkill();
	}

	// SkillWidgets ��������
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