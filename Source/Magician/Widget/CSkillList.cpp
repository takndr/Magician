#include "Widget/CSkillList.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"

#include "Widget/CSkillWidget.h"
#include "Skill/CSkillData.h"

#include "Global.h"

UCSkillList::UCSkillList(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	CHelpers::GetClass(&SkillWidgetClass, "/Game/Widget/WB_Skill");
}

void UCSkillList::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton->OnClicked.IsBound() == false)
	{
		CloseButton->OnClicked.AddDynamic(this, &UCSkillList::OnCloseButtonDown);
	}
}

void UCSkillList::CreateSkillWidget(class UCSkillData* SkillData)
{
	// SkillWidgetClass으로 SkillWidget을 생성하고
	UCSkillWidget* skillWidget = CreateWidget<UCSkillWidget>(GetWorld(), SkillWidgetClass);
	skillWidget->SetSkillWidget(SkillData);

	// Active인지 Passive인지 확인하여 맞는 패널에 Add
	if (SkillData->SkillType == ESkillType::Active)
	{
		//ActivePanel->AddChild(skillWidget);

	}

	if (SkillData->SkillType == ESkillType::Passive)
	{
		//PassivePanel->AddChild(skillWidget);
	}
}

void UCSkillList::OnCloseButtonDown()
{
	//CLog::Print("Close Button Down");
	//CLog::Print(GetOwningPlayer()->GetName());
}