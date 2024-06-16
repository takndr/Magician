#include "Skill/CSkillData.h"

#include "GameFramework/Character.h"

#include "Skill/CSkillEffector.h"

#include "Global.h"

void UCSkillData::BeginPlay(ACharacter* Owner)
{
	OwnerCharacter = Owner;
}

void UCSkillData::DoAction()
{
	CheckTrue(bCoolDown);
	CheckNull(SkillMontage);

	

	if (OnSkillCoolDown.IsBound())
	{
		CLog::Print(SkillName + " Cast");
		OnSkillCoolDown.Broadcast();
	}


	OwnerCharacter->PlayAnimMontage(SkillMontage, SkillMontage->SequenceLength / CastingTime);
}

void UCSkillData::Casting()
{

}

void UCSkillData::CastComplete()
{

}

void UCSkillData::SpawnEffector()
{
	CheckNull(EffectActorClass);
	
	// Owner는 OwnerCharacter, 위치는 일단 Character위치
	FTransform transform = OwnerCharacter->GetActorTransform();
	FVector loc = transform.GetLocation() + OwnerCharacter->GetActorForwardVector() * 50;
	//loc = FVector(loc.X, loc.Y, loc.Z - 88);
	transform.SetLocation(loc);
	CLog::Print("Spawn1");

	FActorSpawnParameters spawnParameter;
	spawnParameter.Owner = OwnerCharacter;

	OwnerCharacter->GetWorld()->SpawnActor<ACSkillEffector>(EffectActorClass, transform, spawnParameter);
}

void UCSkillData::Upgrade()
{
	if (SkillStatus == ESkillStatus::UnLocked)
	{
		SkillStatus = ESkillStatus::Acquired;
	}

	CurrentLevel = FMath::Clamp(CurrentLevel + 1, 0, MaxLevel);
}

void UCSkillData::Downgrade()
{
	CurrentLevel = FMath::Clamp(CurrentLevel - 1, 0, MaxLevel);

	if (CurrentLevel == 0)
	{
		SkillStatus = ESkillStatus::UnLocked;
	}
}

bool UCSkillData::CanLearnedSkill()
{
	return SkillStatus >= ESkillStatus::UnLocked;
}

void UCSkillData::RefreshSkill()
{
	// SkillStatus 관련 업데이트
	if (RequiredSkills.Num() == 0)
	{
		return;
	}

	bool temp = true;
	for (auto skill : RequiredSkills)
	{
		temp &= (skill->SkillStatus == ESkillStatus::Acquired);
	}

	if (temp)
	{
		SkillStatus = ESkillStatus::UnLocked;
	}
	else
	{
		SkillStatus = ESkillStatus::Locked;
	}
}