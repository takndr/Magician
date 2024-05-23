#include "Widget/CSkillQuickSlot.h"

#include "Components/TextBlock.h"

#include "Skill/CSkillData.h"
#include "Widget/CSkillIcon.h"

#include "Global.h"

void UCSkillQuickSlot::NativeConstruct()
{
	KeyName->SetText(KeyText);
	Icon->SetIsQuickSlotIcon(true);
}

UCSkillData* UCSkillQuickSlot::GetSkillInfo()
{
	return Icon->Data;
}