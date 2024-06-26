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
	void UpdateBar(float Percent);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UTexture2D* FillImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* StatBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* StatRemoveBar;

	UPROPERTY(BlueprintReadWrite)
		class UMaterialInstanceDynamic* StatRemoveMaterial;
// ========================================================
};

// Hp�� Mp ũ�� : 350 20

// Xp ũ�� : 805 * 20