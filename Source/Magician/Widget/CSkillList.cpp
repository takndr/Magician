#include "Widget/CSkillList.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

#include "Widget/CSkillWidget.h"
#include "Skill/CSkillData.h"

#include "Player/CPlayer.h"
#include "Component/CSkillComponent.h"

#include "Global.h"

UCSkillList::UCSkillList(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	CHelpers::GetClass(&SkillWidgetClass, "/Game/Widget/WB_Skill");
}

void UCSkillList::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton->OnClicked.IsBound() == false)
	{
		CloseButton->OnClicked.AddDynamic(this, &UCSkillList::OnCloseButtonDown);
	}

	OwningPlayer = Cast<ACharacter>(GetOwningPlayerPawn());
	UpdateSkillPoint();
}

void UCSkillList::CreateSkillWidget(class UCSkillData* SkillData)
{
	// SkillWidgetClass으로 SkillWidget을 생성하고
	UCSkillWidget* skillWidget = CreateWidget<UCSkillWidget>(GetWorld(), SkillWidgetClass);
	skillWidget->SetSkillWidget(SkillData, this);
	SkillWidgets.AddUnique(skillWidget);

	// Active인지 Passive인지 확인하여 맞는 패널에 Add
	if (SkillData->SkillType == ESkillType::Active)
	{
		ActiveScroll->AddChild(skillWidget);
	}

	if (SkillData->SkillType == ESkillType::Passive)
	{
		PassiveScroll->AddChild(skillWidget);
	}
}

void UCSkillList::RefreshSkillWidget()
{
	for (auto skillWidget : SkillWidgets)
	{
		skillWidget->RefreshWidget();
	}
}

void UCSkillList::Attach()
{
	SetVisibility(ESlateVisibility::Visible);

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetHideCursorDuringCapture(true);

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = true;
	controller->SetInputMode(inputMode);
}

void UCSkillList::Detach()
{
	SetVisibility(ESlateVisibility::Collapsed);

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(inputMode);
}

bool UCSkillList::IsOpened()
{
	return GetVisibility() == ESlateVisibility::Visible;
}

void UCSkillList::OnCloseButtonDown()
{
	Detach();
}

void UCSkillList::UpdateSkillPoint() 
{
	CheckNull(OwningPlayer);

	UCSkillComponent* skillComp = CHelpers::GetComponent<UCSkillComponent>(OwningPlayer);
	
	CheckNull(skillComp);

	int skillPoint = skillComp->GetSkillPoints();

	FString str = FString::Printf(TEXT("남은 스킬 포인트 : %d"), skillPoint);
	SkillPoint->SetText(FText::FromString(str));
}