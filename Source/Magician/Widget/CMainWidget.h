#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainWidget.generated.h"

UCLASS()
class MAGICIAN_API UCMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void ControlSkillListWidget();
	void SetSkillList(class UCSkillData* SkillData);

private:
	UPROPERTY(meta = (BindWidget))
		class UUserWidget* Skill1;

	UPROPERTY(meta = (BindWidget))
		class UUserWidget* Skill2;

	UPROPERTY(meta = (BindWidget))
		class UUserWidget* Skill3;

	UPROPERTY(meta = (BindWidget))
		class UUserWidget* Skill4;

	UPROPERTY(meta = (BindWidget))
		class UUserWidget* Skill5;

	UPROPERTY(meta = (BindWidget))
		class UCSkillList* SkillList;
};
