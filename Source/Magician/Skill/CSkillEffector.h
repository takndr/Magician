#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSkillEffector.generated.h"

UCLASS()
class MAGICIAN_API ACSkillEffector : public AActor
{
	GENERATED_BODY()
public:	
	ACSkillEffector();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
// ========================================================
public:
	void SetData(class UCSkillData* Data) { SkillData = Data; }
// ========================================================
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = true))
		class UCSkillData* SkillData;

	UPROPERTY(BlueprintReadWrite)
		TArray<class AActor*> HittedActor;
};
