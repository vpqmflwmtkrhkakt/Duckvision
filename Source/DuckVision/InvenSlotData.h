#pragma once

#include "CoreMinimal.h"
#include "InvenSlotData.generated.h"

// 블루프린트에서 사용 가능하도록 하는 매크로
USTRUCT(BlueprintType)
struct FInvenSlotData
{
	GENERATED_BODY();
	FInvenSlotData() {}

	FInvenSlotData(const FString& ID, UTexture2D* Icon, const int32 Count, const int32 MaxCount, const bool isStackable)
	{
		ItemID = ID;
		InvenIcon = Icon;
		CurrentCount = Count;
		MaxCountPerSlot = MaxCount;
		bIsStackable = isStackable;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InvenIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCountPerSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable = true;
};
