#include "Widget/CSkillWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Widget/CSkillIcon.h"
#include "Skill/CSkillData.h"
#include "Player/CPlayer.h"

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

	SetSkillWidget(Data);

	OwningPlayer = Cast<ACPlayer>(GetOwningPlayerPawn());
}

void UCSkillWidget::OnSkillUpButtonDown()
{
	CLog::Print("Skill Up Button Down");

	// SkillData에 있는 Current Level 증가

	// Skill Component에 있는 Skill Point 감소

	// Skill List 위젯 리프레쉬
}

void UCSkillWidget::OnSkillDownButtonDown()
{
	CLog::Print("Skill Down Button Down");

	// SkillData에 있는 Current Level 감소

	// Skill Component에 있는 Skill Point 증가

	// Skill List 위젯 리프레쉬
}

void UCSkillWidget::SetSkillWidget(class UCSkillData* SkillData)
{
	CheckNull(SkillData);
	Data = SkillData;

	CheckNull(Data);

	Icon->SetIcon(Data);
	CurrentLevel->SetText(FText::FromString(FString::FromInt(Data->CurrentLevel)));
	MaxLevel->SetText(FText::FromString(FString::FromInt(Data->MaxLevel)));
}