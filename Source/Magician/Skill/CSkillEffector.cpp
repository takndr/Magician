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

// Timer함수를 제작
// bp에서 effect마다 다른 매커니즘을 적용
// burned이면 초당 데미지
// Frozen이면 일정 시간동안 멈추게 하기
// ...