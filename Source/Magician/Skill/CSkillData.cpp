#include "Skill/CSkillData.h"

#include "GameFramework/Character.h"

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

	OwnerCharacter->PlayAnimMontage(SkillMontage);
}

void UCSkillData::Casting()
{

}

void UCSkillData::CastComplete()
{

}