#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CWidgetMoveDDO.generated.h"

UCLASS()
class MAGICIAN_API UCWidgetMoveDDO : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (ExposeOnSpawn = true))
		FVector2D DragOffset;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (ExposeOnSpawn = true))
		class UUserWidget* DragWidget;
};
