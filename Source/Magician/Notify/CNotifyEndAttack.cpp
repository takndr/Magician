#include "Notify/CNotifyEndAttack.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Global.h"

FString UCNotifyEndAttack::GetNotifyName_Implementation() const
{
	return "EndAttack";
}

void UCNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{
		UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
		CheckNull(stateComp);

		stateComp->SetIdle();
	}

}