#include "Widget/CStatBar.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Slate/SlateBrushAsset.h"

#include "Global.h"

#define LOCTEXT_NAMESPACE "MyNameSpace"

void UCStatBar::UpdateBar(float Percent, float Max, float Current)
{
	StatBar->SetPercent(Percent);

	FText text = FText::Format(LOCTEXT("ExampleFText", "{0} / {1}"), Current, Max);
	StatText->SetText(text);
}