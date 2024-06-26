#include "Component/CPlayerStatusComponent.h"

#include "Global.h"

UCPlayerStatusComponent::UCPlayerStatusComponent()
{

}

void UCPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentMp = MaxMp;
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
		OnMpChanged.Execute(ratio);
	}
}

void UCPlayerStatusComponent::DecreaseMana(float Dx)
{
	CurrentMp -= Dx;
	CurrentMp = FMath::Clamp(CurrentMp, 0.0f, MaxMp);

	if (OnMpChanged.IsBound())
	{
		float ratio = CurrentMp / MaxMp;
		OnMpChanged.Execute(ratio);
	}
}