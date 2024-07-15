#include "Widget/CStatBar.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Slate/SlateBrushAsset.h"

#include "Global.h"

void UCStatBar::UpdateBar(float Percent, float Max, float Current)
{
	StatBar->SetPercent(Percent);

	FString str = FString::Printf(TEXT("%.0lf / %.0lf"), Current, Max);
	StatText->SetText(FText::FromString(str));
}