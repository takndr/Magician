#include "Widget/CStatBar.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Slate/SlateBrushAsset.h"

#include "Global.h"

void UCStatBar::UpdateBar(float Percent, float Max, float Current)
{
	StatBar->SetPercent(Percent);

	// Current / Max ·Î Text Á¤ÀÇ
	//FText::For
	//FText::Format()
}