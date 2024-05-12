#include "Widget/CMainWidget.h"

#include "Widget/CSkillList.h"

#include "Global.h"

void UCMainWidget::ControlSkillListWidget()
{
	if (SkillList->IsOpened())
	{
		SkillList->Detach();
	}
	else
	{
		SkillList->Attach();
	}
}

void UCMainWidget::SetSkillList(class UCSkillData* SkillData)
{
	SkillList->CreateSkillWidget(SkillData);
}