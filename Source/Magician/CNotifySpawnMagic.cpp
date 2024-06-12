#include "CNotifySpawnMagic.h"

#include "Player/CPlayer.h"
#include "Skill/CSkillData.h"

#include "Global.h"

FString UCNotifySpawnMagic::GetNotifyName_Implementation() const
{
	return "SpawnMagic";
}

void UCNotifySpawnMagic::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	UCSkillData* skillData = player->GetCurrentSkill();

	if (!!skillData)
	{
		skillData->SpawnEffector();
	}
}