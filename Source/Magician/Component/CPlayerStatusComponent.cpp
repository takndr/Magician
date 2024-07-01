#include "Component/CPlayerStatusComponent.h"

#include "Player/CPlayer.h"
#include "Widget/CMainWidget.h"

#include "Global.h"

UCPlayerStatusComponent::UCPlayerStatusComponent()
{

}

void UCPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentMp = MaxMp;

	UCMainWidget* mainWidget = Cast<ACPlayer>(OwnerCharacter)->GetSkillHUDWidget();

	float ratio = FMath::Clamp(CurrentHp / MaxHp, 0.0f, 1.0f);
	mainWidget->UpdateHpBar(ratio, MaxHp, CurrentHp);

	ratio = FMath::Clamp(CurrentMp / MaxMp, 0.0f, 1.0f);
	mainWidget->UpdateMpBar(ratio, MaxMp, CurrentMp);

}

void UCPlayerStatusComponent::RegenMana()
{

}

void UCPlayerStatusComponent::IncreaseMana(float Dx)
{
	CurrentMp += Dx;
	CurrentMp = FMath::Clamp(CurrentHp, 0.0f, MaxMp);

	if (OnMpChanged.IsBound())
	{
		float ratio = CurrentMp / MaxMp;
		OnMpChanged.Execute(ratio, MaxMp, CurrentMp);
	}
}

void UCPlayerStatusComponent::DecreaseMana(float Dx)
{
	CurrentMp -= Dx;
	CurrentMp = FMath::Clamp(CurrentMp, 0.0f, MaxMp);

	if (OnMpChanged.IsBound())
	{
		float ratio = CurrentMp / MaxMp;
		OnMpChanged.Execute(ratio, MaxMp, CurrentMp);
	}
}