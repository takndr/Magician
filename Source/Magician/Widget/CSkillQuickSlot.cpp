#include "Widget/CSkillQuickSlot.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Skill/CSkillData.h"
#include "Widget/CSkillIcon.h"

#include "Global.h"

UCSkillQuickSlot::UCSkillQuickSlot(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	CHelpers::GetAsset(&CoolDownCurve, "/Game/SkillData/SkillCoolDownCurve");
}

void UCSkillQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	KeyName->SetText(KeyText);
	Icon->SetIsQuickSlotIcon(true);

	CoolDownMaterial = SkillCoolDown->GetDynamicMaterial();

	OnTimeline.BindUFunction(this, "CoolDown");
	FinishTimeline.BindUFunction(this, "CoolDownComplete");

	Timeline.AddInterpFloat(CoolDownCurve, OnTimeline);
	Timeline.SetTimelineFinishedFunc(FinishTimeline);
}

bool UCSkillQuickSlot::IsInSkillSlot()
{
	return Icon->Data == nullptr;
}

void UCSkillQuickSlot::DoAction()
{
	Icon->Data->DoAction();

	// 스킬 아이콘 약간 흐릿


	CoolDownMaterial->SetScalarParameterValue("Percent", 1.0f);
	SkillCoolDown->SetVisibility(ESlateVisibility::Visible);

	// 쿨타임 돌아가는거 확인시켜주기
	float time = Icon->Data->SkillCoolDown;
	Timeline.SetPlayRate(1.0f / time);
	Timeline.ReverseFromEnd();
}

void UCSkillQuickSlot::CoolDown(float Output)
{
	CoolDownMaterial->SetScalarParameterValue("Percent", Output);
}

void UCSkillQuickSlot::CoolDownComplete()
{
	CLog::Print("Cool Down End");
	SkillCoolDown->SetVisibility(ESlateVisibility::Collapsed);
}

void UCSkillQuickSlot::SetTickTimeline(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}