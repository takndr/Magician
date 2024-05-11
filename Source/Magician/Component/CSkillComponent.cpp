#include "Component/CSkillComponent.h"

#include "Player/CPlayer.h"
#include "Widget/CMainWidget.h"

#include "Skill/CSkillData.h"

#include "Global.h"

UCSkillComponent::UCSkillComponent()
{

}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	ACPlayer* player = Cast<ACPlayer>(GetOwner());

	// �÷��̾��� skill list widget�� ��������

	// TArray<SkillData> Skills�� �迭�� ���鼭 skill list widget�� �߰�
	for (auto skill : Skills)
	{
		//player->GetSkillHUDWidget()->SetSkillList(skill);
	}
}

void UCSkillComponent::IncreaseSkillPoints(uint8 Point)
{
	SkillPoints += Point;
}

void UCSkillComponent::DecreaseSkillPoints(uint8 Point)
{
	SkillPoints -= Point;
}