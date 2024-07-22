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
// AController
EStatusEffect UCDamageComponent::TriggerEffect(EStatusEffect effect, class AController* Instigator)
{
	switch (effect)
	{
	case EStatusEffect::Burned:
		BurnedEffect();
		break;
	case EStatusEffect::Frozen:
		FrozenEffect();
		break;
	default:
		break;
	}

	return effect;
}

void UCDamageComponent::BurnedEffect()
{
	// Spawn Effector
	FTransform transform = OwnerCharacter->GetActorTransform();

	ACSkillEffector* skillEffector;
	skillEffector = GetWorld()->SpawnActorDeferred<ACSkillEffector>(Effector[EStatusEffect::Burned], transform, OwnerCharacter);
	//skillEffector->SetInstigator();
	skillEffector->FinishSpawning(transform);
}

void UCDamageComponent::FrozenEffect()
{
	// Spawn Effector
	FTransform transform = OwnerCharacter->GetActorTransform();

	ACSkillEffector* skillEffector;
	skillEffector = GetWorld()->SpawnActorDeferred<ACSkillEffector>(Effector[EStatusEffect::Frozen], transform, OwnerCharacter);
	//skillEffector->SetInstigator();
	skillEffector->FinishSpawning(transform);
}


