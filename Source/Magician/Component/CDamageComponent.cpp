#include "Component/CDamageComponent.h"

#include "Skill/CSkillEffector.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"

#include "Global.h"

UCDamageComponent::UCDamageComponent()
{
	TSubclassOf<ACSkillEffector> effector;

	CHelpers::GetClass(&effector, "/Game/SkillData/SkillEffector/BP_BurnedEffect");
	Effector.Add(EStatusEffect::Burned, effector);

	CHelpers::GetClass(&effector, "/Game/SkillData/SkillEffector/BP_FrozenEffect");
	Effector.Add(EStatusEffect::Frozen, effector);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	
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

	// Spawn Effector -> Owner�� OwnerCharacter��
	// ���� ������ SkillEffector�� ���� �ٸ��� ����

	// �ʴ� ������ �ֱ� -> BP��
}

void UCDamageComponent::FrozenEffect()
{
	CLog::Print("Frozen!");

	// Spawn Effector

	// ĳ���� ���߰� ���� �ð� �ڿ� �ٽ� �����̰� �ϱ� -> BP��
}


