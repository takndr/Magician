#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSkillDetail.generated.h"

UCLASS()
class MAGICIAN_API UCSkillDetail : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void SettingDetail(class UCSkillData* SkillData);

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* Icon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillType;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillDamage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillDes;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillMLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PreSkillName;
};
