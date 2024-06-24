#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSkillActor.generated.h"

UCLASS()
class MAGICIAN_API ACSkillActor : public AActor
{
	GENERATED_BODY()
public:	
	ACSkillActor();
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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf<class UDamageType> DamageTypeClass;
};
