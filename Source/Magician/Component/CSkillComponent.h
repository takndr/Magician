#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICIAN_API UCSkillComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCSkillComponent();
protected:
	virtual void BeginPlay() override;
//===================================================================
public:
	void UpgradeSkill(class UCSkillData* Skill);
	void DowngradeSkill(class UCSkillData* Skill);

	void IncreaseSkillPoints(int Point);
	void DecreaseSkillPoints(int Point);

	int GetSkillPoints() { return SkillPoints; }
//===================================================================
public:
	UPROPERTY(EditDefaultsOnly)
		int SkillPoints;
//===================================================================

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<class UCSkillData*> Skills;

	UPROPERTY(EditDefaultsOnly)
		TArray<class AActor*> SkillsTest;

//===================================================================

};


