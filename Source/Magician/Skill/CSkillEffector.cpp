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

// TODO : �� ĳ���Ͱ� ������ �ִ� ���͸������ ���̳ʹ͸��͸��� �迭�� ����
// ���� ����Ʈ�� �ɸ��� �Ǹ� N�ʵ��� ��� ���͸����� ������ �Ķ������� ������ ��, �̵� ���ѽ�Ű�� �ð��� ������ ���͸����� �����Ǹ鼭 �̵��� �����ϰԲ�
// ȭ�� ����Ʈ�� �ɸ��� �Ǹ� ƽ �������� �� �� ���� ���͸������ ���������� ���� �� �ٷ� ����
// ĳ���͸��� ���� �����Ϸ��� Interface�� ����? �ϴ°� �� �� ���������� ���
// Effector�� GetOwner�� Interface�� Cast�� �Ŀ� Interface���� �ִ� �Լ��� ȣ���� �� �ֵ���