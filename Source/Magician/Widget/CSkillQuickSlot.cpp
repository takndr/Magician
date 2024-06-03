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

	// ��ų ������ �ణ �帴
	CoolDownMaterial->SetScalarParameterValue("Percent", 1.0f);
	SkillCoolDown->SetVisibility(ESlateVisibility::Visible);

	// ��Ÿ�� ���ư��°� Ȯ�ν����ֱ�
	float time = Icon->Data->SkillCoolDown;
	Timeline.SetPlayRate(1.0f / time);
	Timeline.ReverseFromEnd();

	// ��ų ��Ÿ�� ���� ���̶�� ����
	Icon->Data->SetCoolDown(true);
}

// CoolDown Ÿ�Ӷ��� ���� ȣ��Ǵ� �Լ�
void UCSkillQuickSlot::CoolDown(float Output)
{
	CoolDownMaterial->SetScalarParameterValue("Percent", Output);
}

// CoolDown Ÿ�Ӷ����� ������ �� ȣ��Ǵ� �Լ�
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