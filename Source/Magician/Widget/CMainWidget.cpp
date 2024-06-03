#include "Widget/CMainWidget.h"

#include "Skill/CSkillData.h"
#include "Widget/CSkillList.h"
#include "Widget/CSkillQuickSlot.h"

#include "Player/CPlayer.h"

#include "Global.h"

void UCMainWidget::NativeConstruct()
{
	OwningPlayer = Cast<ACPlayer>(GetOwningPlayerPawn());

	OwningPlayer->Skill1Signature.BindUFunction(this, "DoSkill1");
	OwningPlayer->Skill2Signature.BindUFunction(this, "DoSkill2");
	OwningPlayer->Skill3Signature.BindUFunction(this, "DoSkill3");
	OwningPlayer->Skill4Signature.BindUFunction(this, "DoSkill4");
	OwningPlayer->Skill5Signature.BindUFunction(this, "DoSkill5");
}

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

void UCMainWidget::DoSkill1()
{
	SelectSkill(Skill1);
}
void UCMainWidget::DoSkill2()
{
	SelectSkill(Skill2);
}

void UCMainWidget::DoSkill3()
{
	SelectSkill(Skill3);
}

void UCMainWidget::DoSkill4()
{
	SelectSkill(Skill4);
}

void UCMainWidget::DoSkill5()
{
	SelectSkill(Skill5);
}

void UCMainWidget::SelectSkill(class UCSkillQuickSlot* SkillSlot)
{
	if (SkillSlot->IsInSkillSlot())
	{
		CLog::Print("No Skill In Quick Slot5");
	}
	else
	{
		UCSkillData* skillData = SkillSlot->GetInSkillSlot();

		if (skillData == OwningPlayer->GetCurrentSkill())
		{
			OffAllSkill();
			OwningPlayer->SetCurrentSkill(nullptr);
		}
		else
		{
			OffAllSkill();
			SkillSlot->OnSelected();
			OwningPlayer->SetCurrentSkill(skillData);
		}
	}
}

void UCMainWidget::OffAllSkill()
{
	Skill1->OffSelected();
	Skill2->OffSelected();
	Skill3->OffSelected();
	Skill4->OffSelected();
	Skill5->OffSelected();
}