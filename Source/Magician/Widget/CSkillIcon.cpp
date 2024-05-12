#include "Widget/CSkillIcon.h"

#include "Components/Image.h"

#include "Skill/CSkillData.h"

#include "Global.h"

void UCSkillIcon::NativeConstruct()
{
	Super::NativeConstruct();

	SetDefaultSetting();
}

void UCSkillIcon::SetIcon(UCSkillData* SkillData)
{
	CheckNull(SkillData);

	Data = SkillData;

	// Icon Image ¼¼ÆÃ
	FSlateBrush brush;
	FLinearColor color(1, 1, 1, 1);
	brush.SetResourceObject(Data->SkillIcon);
	brush.TintColor = color;
	brush.DrawAs = ESlateBrushDrawType::Image;

	//Icon->SetBrushFromTexture(Data->SkillIcon);
	Icon->SetBrush(brush);
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
	CheckNullResult(Data, false);

	return Data->SkillType == ESkillType::Active;
}

void UCSkillIcon::SetDefaultSetting()
{
	FSlateBrush brush;
	FLinearColor color(1, 1, 1, 0);
	brush.SetResourceObject(nullptr);
	brush.TintColor = color;
	brush.DrawAs = ESlateBrushDrawType::Image;

	Icon->SetBrush(brush);
}