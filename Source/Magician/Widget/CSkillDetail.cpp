#include "Widget/CSkillDetail.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Skill/CSkillData.h"

#include "Global.h"

void UCSkillDetail::SettingDetail(UCSkillData* SkillData)
{
	FString temp = "";

	Icon->SetBrushFromTexture(SkillData->SkillIcon);

	temp = SkillData->SkillName;
	SkillName->SetText(FText::FromString(temp));

	if (SkillData->SkillType == ESkillType::Active)
	{
		SkillType->SetText(FText::FromString("Active"));
		temp = SkillDamage->GetText().ToString();
		temp += FString::FromInt(SkillData->SkillDamage);
		SkillDamage->SetText(FText::FromString(temp));
	}
	else
	{
		SkillType->SetText(FText::FromString("Passive"));
		SkillDamage->SetVisibility(ESlateVisibility::Hidden);
	}

	temp = SkillDes->GetText().ToString();
	SkillDes->SetText(FText::FromString(temp));

	temp = SkillLevel->GetText().ToString();
	temp += FString::FromInt(SkillData->CurrentLevel);
	SkillLevel->SetText(FText::FromString(temp));

	temp = SkillMLevel->GetText().ToString();
	temp += FString::FromInt(SkillData->MaxLevel);
	SkillMLevel->SetText(FText::FromString(temp));

	if (SkillData->RequiredSkills.Num() != 0)
	{
		temp = PreSkillName->GetText().ToString();

		for (auto required : SkillData->RequiredSkills)
		{
			temp += required->SkillName + " ";
		}
		
		PreSkillName->SetText(FText::FromString(temp));
	}
	else
	{
		PreSkillName->SetVisibility(ESlateVisibility::Hidden);
	}

}