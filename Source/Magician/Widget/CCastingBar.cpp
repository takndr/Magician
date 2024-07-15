#include "Widget/CCastingBar.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Player/CPlayer.h"
#include "Skill/CSkillData.h"

#include "Global.h"

UCCastingBar::UCCastingBar(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	CHelpers::GetAsset(&CoolDownCurve, "/Game/SkillData/SkillCoolDownCurve");
}

void UCCastingBar::NativeConstruct()
{
	Super::NativeConstruct();

	OnTimeline.BindUFunction(this, "Casting");
	FinishTimeline.BindUFunction(this, "Detach");

	Timeline.AddInterpFloat(CoolDownCurve, OnTimeline);
	Timeline.SetTimelineFinishedFunc(FinishTimeline);
}

void UCCastingBar::Attach()
{
	SetVisibility(ESlateVisibility::Visible);

	UCSkillData* skill = Cast<ACPlayer>(GetOwningPlayer()->GetPawn())->GetCurrentSkill();

	// 캐스팅 타임라인 시작
	float time = skill->CastingTime;
	Timeline.SetPlayRate(1.0f / time);
	Timeline.PlayFromStart();

	// 텍스트 이름 변경
	FString str = FString::Printf(TEXT("%s 시전중..."), *skill->SkillName);
	CastingText->SetText(FText::FromString(str));
}

void UCCastingBar::Detach()
{
	SetVisibility(ESlateVisibility::Hidden);

	if (Timeline.IsPlaying())
	{
		Timeline.Stop();
	}

	CastingBar->SetPercent(0.0f);
}

void UCCastingBar::Casting(float Output)
{
	CastingBar->SetPercent(Output);
}

void UCCastingBar::SetTickTimeline(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

// TODO : 캐스팅 관련 작업 마무리
// 캐스팅 시작할 때 타임라인 돌아가게
// 도중에 움직였을 때 타임라인 스탑시키며, 위젯 안보이게
// 캐스팅 완료되었을 때 위젯 안보이게