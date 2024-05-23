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

	// SkillData�� �ִ� Current Level ����

	// Skill Component�� �ִ� Skill Point ����

	// Skill List ���� ��������
}

void UCSkillWidget::OnSkillDownButtonDown()
{
	CLog::Print("Skill Down Button Down");

	// SkillData�� �ִ� Current Level ����

	// Skill Component�� �ִ� Skill Point ����

	// Skill List ���� ��������
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