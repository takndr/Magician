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

	// �ʴ� ������ �ֱ� -> BP��
}

void UCDamageComponent::FrozenEffect()
{
	CLog::Print("Frozen!");

	// Spawn Effector

	// ĳ���� ���߰� ���� �ð� �ڿ� �ٽ� �����̰� �ϱ� -> BP��
}


