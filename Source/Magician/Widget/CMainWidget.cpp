#include "Widget/CMainWidget.h"

#include "Widget/CSkillList.h"

#include "Global.h"

void UCMainWidget::OpenSkillListWidget()
{
	SkillList->SetVisibility(ESlateVisibility::Visible);
}

void UCMainWidget::CloseSkillListWidget()
{
	SkillList->SetVisibility(ESlateVisibility::Collapsed);
}

void UCMainWidget::SetSkillList(class UCSkillData* SkillData)
{
	SkillList->CreateSkillWidget(SkillData);
}