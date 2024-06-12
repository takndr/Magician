#include "Widget/CSkillWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Component/CSkillComponent.h"

#include "Widget/CSkillIcon.h"
#include "Widget/CSkillList.h"
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

	OwningPlayer = Cast<ACharacter>(GetOwningPlayerPawn());
	SkillComp = CHelpers::GetComponent<UCSkillComponent>(OwningPlayer);
}

void UCSkillWidget::OnSkillUpButtonDown()
{
	CheckNull(SkillComp);

	// SkillData를 Upgrade
	SkillComp->UpgradeSkill(Data);

	UpdateCurrentLevel();
	RefreshWidget();

	// Skill List 위젯 리프레쉬
	if (!!SkillListWidget)
	{
		SkillListWidget->UpdateSkillPoint();
	}
}

void UCSkillWidget::OnSkillDownButtonDown()
{
	CheckNull(SkillComp);

	// SkillData를 Downgrade
	SkillComp->DowngradeSkill(Data);

	UpdateCurrentLevel();
	RefreshWidget();

	// Skill List 위젯 리프레쉬
	if (!!SkillListWidget)
	{
		SkillListWidget->UpdateSkillPoint();
	}
}

void UCSkillWidget::SetSkillWidget(class UCSkillData* SkillData, class UCSkillList* ListWidget)
{
	CheckNull(SkillData);
	Data = SkillData;

	Icon->SetIcon(Data);

	if (Data->SkillType == ESkillType::Active)
	{
		SkillType->SetText(FText::FromString("Active"));
	}

	if (Data->SkillType == ESkillType::Passive)
	{
		SkillType->SetText(FText::FromString("Passive"));
	}

	SkillName->SetText(FText::FromString(Data->SkillName));

	UpdateCurrentLevel();
	UpdateMaxLevel();
	RefreshWidget();

	SkillListWidget = ListWidget;
}

void UCSkillWidget::RefreshWidget()
{
	if (Data->CanLearnedSkill())
	{
		SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
	else
	{
		SetColorAndOpacity(FLinearColor(0.5, 0.5, 0.5, 0.5));
		SkillUpButton->SetVisibility(ESlateVisibility::Hidden);
		SkillDownButton->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (Data->CurrentLevel == Data->MaxLevel)
	{
		SkillUpButton->SetVisibility(ESlateVisibility::Hidden);
		SkillDownButton->SetVisibility(ESlateVisibility::Visible);
	}
	else if (Data->CurrentLevel == 0)
	{
		SkillUpButton->SetVisibility(ESlateVisibility::Visible);
		SkillDownButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SkillUpButton->SetVisibility(ESlateVisibility::Visible);
		SkillDownButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCSkillWidget::UpdateCurrentLevel()
{
	CurrentLevel->SetText(FText::FromString(FString::FromInt(Data->CurrentLevel)));
}

void UCSkillWidget::UpdateMaxLevel()
{
	MaxLevel->SetText(FText::FromString(FString::FromInt(Data->MaxLevel)));
}
