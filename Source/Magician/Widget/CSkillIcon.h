#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSkillIcon.generated.h"

UCLASS()
class MAGICIAN_API UCSkillIcon : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;



protected:
	UFUNCTION(BlueprintCallable)
		void RefreshWidget();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsActiveSkill();

private:
	void SetDefaultSetting();

public:
	void SetIcon(class UCSkillData* SkillData);
	void SetIsQuickSlotIcon(bool bSlot) { IsInQuickSlot = bSlot; }


public:
	UPROPERTY(BlueprintReadWrite)
		class UCSkillData* Data;

protected:
	UPROPERTY(BlueprintReadWrite)
		class UCSkillDetail* SkillDetail;
	
	UPROPERTY(BlueprintReadWrite)
		bool IsInQuickSlot = false;

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* Icon;
};
