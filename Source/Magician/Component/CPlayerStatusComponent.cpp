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

	timerHandle = UKismetSystemLibrary::K2_SetTimer(this, "RegenMana", 1, true);
	if (CurrentMp == MaxMp)
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), timerHandle);
	}
}

void UCPlayerStatusComponent::RegenMana()
{
	IncreaseMana(MpRegen);
}

void UCPlayerStatusComponent::IncreaseMana(float Dx)
{
	CurrentMp += Dx;
	CurrentMp = FMath::Clamp(CurrentMp, 0.0f, MaxMp);

	if (CurrentMp == MaxMp)
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), timerHandle);
	}

	if (OnMpChanged.IsBound())
	{
		float ratio = CurrentMp / MaxMp;
		OnMpChanged.Execute(ratio, MaxMp, CurrentMp);
	}
}

void UCPlayerStatusComponent::DecreaseMana(float Dx)
{
	if (CurrentMp == MaxMp)
	{
		UKismetSystemLibrary::K2_UnPauseTimerHandle(GetWorld(), timerHandle);
	}

	CurrentMp -= Dx;
	CurrentMp = FMath::Clamp(CurrentMp, 0.0f, MaxMp);

	if (OnMpChanged.IsBound())
	{
		float ratio = CurrentMp / MaxMp;
		OnMpChanged.Execute(ratio, MaxMp, CurrentMp);
	}
}