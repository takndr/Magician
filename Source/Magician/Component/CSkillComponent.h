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
	void IncreaseSkillPoints(uint8 Point);
	void DecreaseSkillPoints(uint8 Point);

	uint8 GetSkillPoints() { return SkillPoints; }
//===================================================================
public:
	UPROPERTY(EditDefaultsOnly)
		uint8 SkillPoints;
//===================================================================

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<class UCSkillData*> Skills;

	UPROPERTY(EditDefaultsOnly)
		TArray<class AActor*> SkillsTest;
};
