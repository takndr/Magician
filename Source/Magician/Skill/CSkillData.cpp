#include "Skill/CSkillData.h"

#include "GameFramework/Character.h"

#include "Skill/CSkillActor.h"
#include "Player/CPlayer.h"
#include "Widget/CMainWidget.h"
#include "Component/CPlayerStatusComponent.h"

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
		OnSkillCoolDown.Broadcast();
	}

	OwnerCharacter->PlayAnimMontage(SkillMontage, SkillMontage->SequenceLength / CastingTime);
}

void UCSkillData::Casting()
{
	CheckTrue(bCoolDown);
	CheckNull(SkillMontage);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	player->GetMainHUDWidget()->CastingStart();

	OwnerCharacter->PlayAnimMontage(SkillMontage, SkillMontage->SequenceLength / CastingTime);
}

void UCSkillData::CastComplete()
{
	if (OnSkillCoolDown.IsBound())
	{
		OnSkillCoolDown.Broadcast();
	}

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	player->GetMainHUDWidget()->CastingEnd();
}

void UCSkillData::SpawnEffector()
{
	CheckNull(SkillActorClass);

	FTransform transform;
	ACSkillActor* skillActor;
	skillActor = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACSkillActor>(SkillActorClass, transform, OwnerCharacter);
	skillActor->SetData(this);
	skillActor->FinishSpawning(transform);
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

	if (CurrentLevel != 0)
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