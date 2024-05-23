#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSkillQuickSlot.generated.h"

UCLASS()
class MAGICIAN_API UCSkillQuickSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	class UCSkillData* GetSkillInfo();

protected:
	UPROPERTY(EditAnywhere)
		FText KeyText;

private:
	UPROPERTY(meta = (BindWidget))
		class UCSkillIcon* Icon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* KeyName;

};
