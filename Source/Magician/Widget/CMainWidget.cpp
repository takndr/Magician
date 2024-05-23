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
	if (Skill1->GetSkillInfo() == nullptr)
	{
		CLog::Print("No Skill In Quick Slot1");
	}
	else
	{
		Skill1->GetSkillInfo()->DoAction();
	}
}
void UCMainWidget::DoSkill2()
{
	if (Skill2->GetSkillInfo() == nullptr)
	{
		CLog::Print("No Skill In Quick Slot2");
	}
	else
	{
		Skill2->GetSkillInfo()->DoAction();
	}
}

void UCMainWidget::DoSkill3()
{
	if (Skill3->GetSkillInfo() == nullptr)
	{
		CLog::Print("No Skill In Quick Slot3");
	}
	else
	{
		Skill3->GetSkillInfo()->DoAction();
	}
}

void UCMainWidget::DoSkill4()
{
	if (Skill4->GetSkillInfo() == nullptr)
	{
		CLog::Print("No Skill In Quick Slot4");
	}
	else
	{
		Skill4->GetSkillInfo()->DoAction();
	}
}

void UCMainWidget::DoSkill5()
{
	if (Skill5->GetSkillInfo() == nullptr)
	{
		CLog::Print("No Skill In Quick Slot5");
	}
	else
	{
		Skill5->GetSkillInfo()->DoAction();
	}
}
