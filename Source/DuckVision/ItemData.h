#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

// 블루프린트에서 사용 가능하도록 하는 매크로
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY();

	FItemData() : ItemID(TEXT("")), InvenIcon(nullptr), CurrentCount(0), MaxCountPerSlot(0) {}
	FItemData(const FString& ID, UTexture2D* Icon, const int32 Count, const int32 MaxCount, const bool isStackable) : ItemID(ID), InvenIcon(Icon), CurrentCount(Count), MaxCountPerSlot(MaxCount), bIsStackable(isStackable) {}

	// 블루프린트 에디터에서 보이게 하고 수정 가능하도록
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
