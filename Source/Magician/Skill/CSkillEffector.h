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

public:
	void SetInstigator(class AController* Insti);

private:
	class AController* Instigator;
};
