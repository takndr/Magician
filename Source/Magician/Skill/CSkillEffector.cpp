#include "Skill/CSkillEffector.h"

#include "Global.h"

ACSkillEffector::ACSkillEffector()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACSkillEffector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSkillEffector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSkillEffector::SetInstigator(class AController* Insti)
{
	Instigator = Insti;
}

// TODO : 각 캐릭터가 가지고 있는 머터리얼들을 다이너믹머터리얼 배열로 저장
// 빙결 이펙트에 걸리게 되면 N초동안 모든 머터리얼의 색상을 파란색으로 변경한 후, 이동 제한시키고 시간이 지나면 머터리얼이 원복되면서 이동이 가능하게끔
// 화염 이펙트에 걸리게 되면 틱 데미지가 들어갈 때 마다 머터리얼들을 붉은색으로 변경 후 바로 원복
// 캐릭터마다 전부 지정하려면 Interface로 관리? 하는게 좀 더 간편할지는 고민
// Effector쪽 GetOwner를 Interface로 Cast한 후에 Interface내에 있는 함수를 호출할 수 있도록