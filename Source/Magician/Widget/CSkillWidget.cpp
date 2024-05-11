#include "Widget/CSkillWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Widget/CSkillIcon.h"
#include "Skill/CSkillData.h"

#include "Global.h"

void UCSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SkillUpButton->OnClicked.IsBound() == false)
	{
		SkillUpButton->OnClicked.AddDynamic(this, &UCSkillWidget::OnSkillUpButtonDown);
	}

	if (SkillDownButton->OnClicked.IsBound() == false)
	{
		SkillDownButton->OnClicked.AddDynamic(this, &UCSkillWidget::OnSkillDownButtonDown);
	}
}

void UCSkillWidget::OnSkillUpButtonDown()
{
	CLog::Print("Skill Up Button Down");
}

void UCSkillWidget::OnSkillDownButtonDown()
{
	CLog::Print("Skill Down Button Down");
}

void UCSkillWidget::SetSkillWidget(class UCSkillData* SkillData)
{
	CheckNull(SkillData);
	Data = SkillData;

	CheckNull(Data);

	//Icon->SetIcon(Data);
	CurrentLevel->SetText(FText::FromString(FString::FromInt(Data->CurrentLevel)));
	MaxLevel->SetText(FText::FromString(FString::FromInt(Data->MaxLevel)));
}