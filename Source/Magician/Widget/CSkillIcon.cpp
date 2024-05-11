#include "Widget/CSkillIcon.h"

#include "Components/Image.h"

#include "Skill/CSkillData.h"

#include "Global.h"

void UCSkillIcon::SetIcon(UCSkillData* SkillData)
{
	Data = SkillData;

	// Icon Image ¼¼ÆÃ
	Icon->SetBrushFromTexture(Data->SkillIcon);
}

void UCSkillIcon::RefreshWidget()
{
	if (!!Data)
	{
		Data->SkillIcon;
		Icon->SetBrushFromTexture(Data->SkillIcon);
	}
	else
	{

	}
}

bool UCSkillIcon::IsActiveSkill()
{
	return Data->SkillType == ESkillType::Active;
}