#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "InvenSlotData.generated.h"

// 블루프린트에서 사용 가능하도록 하는 매크로
USTRUCT(BlueprintType)
struct FInvenSlotData
{
	GENERATED_BODY();
	FInvenSlotData() {}
	FInvenSlotData(const FItemData& InputItemData, const int32 Index) : IsEmpty(false), SlotIndex(Index), ItemData(InputItemData) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsEmpty = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;
};
