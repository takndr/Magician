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

	// Spawn Effector -> Owner은 OwnerCharacter로
	// 이후 설정은 SkillEffector에 따라서 다르게 진행

	// 초당 데미지 주기 -> BP로
}

void UCDamageComponent::FrozenEffect()
{
	CLog::Print("Frozen!");

	// Spawn Effector

	// 캐릭터 멈추고 일정 시간 뒤에 다시 움직이게 하기 -> BP로
}


