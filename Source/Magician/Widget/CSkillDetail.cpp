#include "Widget/CSkillDetail.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Skill/CSkillData.h"

#include "Global.h"

//FString str = FString::Printf(TEXT("%.0lf / %.0lf"), Current, Max);
//StatText->SetText(FText::FromString(str));

void UCSkillDetail::SettingDetail(UCSkillData* SkillData)
{
	FString str = "";

	Icon->SetBrushFromTexture(SkillData->SkillIcon);

	str = FString::Printf(TEXT("%s"), *SkillData->SkillName);
	SkillName->SetText(FText::FromString(str));

	if (SkillData->SkillType == ESkillType::Active)
	{
		SkillType->SetText(FText::FromString("Active"));
		str = FString::Printf(TEXT("스킬 데미지 : %.0lf"), SkillData->SkillDamage);
		SkillDamage->SetText(FText::FromString(str));
	}
	else
	{
		SkillType->SetText(FText::FromString("Passive"));
		SkillDamage->SetVisibility(ESlateVisibility::Hidden);
	}

	//str = FString::Printf(TEXT("%s"), *SkillData->SkillDetails);
	str = SkillData->SkillDetails.Replace(L"/n", L"\n");
	SkillDes->SetText(FText::FromString(str));

	str = FString::Printf(TEXT("현재 레벨 : %d"), SkillData->CurrentLevel);
	SkillLevel->SetText(FText::FromString(str));

	str = FString::Printf(TEXT("최대 레벨 : %d"), SkillData->MaxLevel);
	SkillMLevel->SetText(FText::FromString(str));

	if (SkillData->RequiredSkills.Num() != 0)
	{
		str = PreSkillName->GetText().ToString();

		for (auto required : SkillData->RequiredSkills)
		{
			str += required->SkillName + " ";
		}
		
		PreSkillName->SetText(FText::FromString(str));
	}
	else
	{
		PreSkillName->SetVisibility(ESlateVisibility::Hidden);
	}

}