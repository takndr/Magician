#include "Component/CDamageComponent.h"

#include "Skill/CSkillEffector.h"

#include "Global.h"

UCDamageComponent::UCDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TSubclassOf<ACSkillEffector> effector;

	CHelpers::GetClass(&effector, "/Game/SkillData/SkillEffector/BP_BurnedEffect");
	Effector.Add(EStatusEffect::Burned, effector);

	CHelpers::GetClass(&effector, "/Game/SkillData/SkillEffector/BP_FrozenEffect");
	Effector.Add(EStatusEffect::Frozen, effector);
}

void UCDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCDamageComponent::TriggerEffect(EStatusEffect effect)
{
	switch (effect)
	{
	case EStatusEffect::None:
		break;
	case EStatusEffect::Burned:
		BurnedEffect();
		break;
	case EStatusEffect::Frozen:
		FrozenEffect();
		break;
	default:
		break;
	}
}

void UCDamageComponent::BurnedEffect()
{
	CLog::Print("Burning!");

	// Spawn Effector

	// 초당 데미지 주기 -> BP로
}

void UCDamageComponent::FrozenEffect()
{
	CLog::Print("Frozen!");

	// Spawn Effector

	// 캐릭터 멈추고 일정 시간 뒤에 다시 움직이게 하기 -> BP로
}


