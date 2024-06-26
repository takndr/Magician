#include "Widget/CStatBar.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Slate/SlateBrushAsset.h"

#include "Global.h"

void UCStatBar::UpdateBar(float Percent)
{
	StatBar->SetPercent(Percent);
}