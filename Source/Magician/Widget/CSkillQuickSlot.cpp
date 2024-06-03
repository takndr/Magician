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

	//Icon->Data->OnSkillCoolDown.AddDynamic(this, &UCSkillQuickSlot::DoAction);
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

void UCSkillQuickSlot::DoAction()
{
	//CheckTrue(Icon->Data->IsCoolDown());
	//Icon->Data->DoAction();

	// 스킬 아이콘 약간 흐릿
	CoolDownMaterial->SetScalarParameterValue("Percent", 1.0f);
	SkillCoolDown->SetVisibility(ESlateVisibility::Visible);

	// 쿨타임 돌아가는거 확인시켜주기
	float time = Icon->Data->SkillCoolDown;
	Timeline.SetPlayRate(1.0f / time);
	Timeline.ReverseFromEnd();

	// 스킬 쿨타임 도는 중이라고 설정
	Icon->Data->SetCoolDown(true);
}

// CoolDown 타임라인 동안 호출되는 함수
void UCSkillQuickSlot::CoolDown(float Output)
{
	CoolDownMaterial->SetScalarParameterValue("Percent", Output);
}

// CoolDown 타임라인이 끝났을 때 호출되는 함수
void UCSkillQuickSlot::CoolDownComplete()
{
	SkillCoolDown->SetVisibility(ESlateVisibility::Collapsed);
	Icon->Data->SetCoolDown(false);
}

void UCSkillQuickSlot::SetTickTimeline(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCSkillQuickSlot::BindCoolDown()
{
	if (Icon->Data->OnSkillCoolDown.IsBound())
	{
		Icon->Data->OnSkillCoolDown.Clear();
	}
	Icon->Data->OnSkillCoolDown.AddDynamic(this, &UCSkillQuickSlot::DoAction);
	CLog::Print("1");
}

bool UCSkillQuickSlot::IsInSkillSlot()
{ 
	return Icon->Data == nullptr; 
}

class UCSkillData* UCSkillQuickSlot::GetInSkillSlot()
{
	return Icon->Data;
}

void UCSkillQuickSlot::OnSelected()
{
	SkillSelected->SetVisibility(ESlateVisibility::Visible);
}

void UCSkillQuickSlot::OffSelected()
{
	SkillSelected->SetVisibility(ESlateVisibility::Hidden);
}