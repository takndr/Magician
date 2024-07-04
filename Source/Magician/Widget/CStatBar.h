#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CStatBar.generated.h"

UCLASS()
class MAGICIAN_API UCStatBar : public UUserWidget
{
	GENERATED_BODY()
// ========================================================
public:
	friend class UCMainWidget;
// ========================================================
private:
	void UpdateBar(float Percent, float Max, float Current);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UTexture2D* FillImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* StatBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* StatRemoveBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatText;

	UPROPERTY(BlueprintReadWrite)
		class UMaterialInstanceDynamic* StatRemoveMaterial;
// ========================================================
};

// Hp와 Mp 크기 : 350 20

// Xp 크기 : 805 * 20