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

	// 플레이어의 skill list widget을 가져오고

	// TArray<SkillData> Skills의 배열을 돌면서 skill list widget에 추가
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