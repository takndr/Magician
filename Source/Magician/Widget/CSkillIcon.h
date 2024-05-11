#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSkillIcon.generated.h"

UCLASS()
class MAGICIAN_API UCSkillIcon : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UCSkillData* Data;

protected:
	UFUNCTION(BlueprintCallable)
		void RefreshWidget();

	UFUNCTION(BlueprintCallable)
		bool IsActiveSkill();

public:
	void SetIcon(class UCSkillData* SkillData);

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* Icon;
};
