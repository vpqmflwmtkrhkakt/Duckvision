// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "DebugHelper.h"
#include "UISubsystem.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InvenDatas.Reserve(InventorySize);
}

FItemData UInventoryComponent::AddItem(FItemData ItemData)
{
	for (int32 i = 0; i < InvenDatas.Num(); ++i)
	{
		if (InvenDatas[i].ItemData.ItemID == ItemData.ItemID)
		{
			if (InvenDatas[i].ItemData.CurrentCount < InvenDatas[i].ItemData.MaxCountPerSlot)
			{
				const int32 AddableCount = InvenDatas[i].ItemData.MaxCountPerSlot - InvenDatas[i].ItemData.CurrentCount;

				const int32 AddCount = FMath::Min(ItemData.CurrentCount, AddableCount);

				InvenDatas[i].ItemData.CurrentCount += AddCount;

				ItemData.CurrentCount -= AddCount;

				OnItemUpdated.Broadcast(i, InvenDatas[i]);

				if (ItemData.CurrentCount <= 0) return ItemData;
			}
		}
	}

	while (ItemData.CurrentCount > 0 && InvenDatas.Num() < InventorySize)
	{
		const int32 AddCount = FMath::Min(ItemData.CurrentCount, ItemData.MaxCountPerSlot);

		FInvenSlotData SlotData(ItemData, InvenDatas.Num());

		InvenDatas.Add(SlotData);

		OnItemUpdated.Broadcast(InvenDatas.Num() - 1, SlotData);
		ItemData.CurrentCount -= AddCount;
	}

	return ItemData;
}

void UInventoryComponent::UpdateItemData(const int32 Index, FItemData& ItemData)
{
	if (!InvenDatas.IsValidIndex(Index)) return;

	InvenDatas[Index].ItemData = ItemData;
	if (InvenDatas[Index].ItemData.CurrentCount <= 0)
	{
		InvenDatas[Index].IsEmpty = true;
	}

	OnItemUpdated.Broadcast(Index, InvenDatas[Index]);
}

void UInventoryComponent::RemoveItem(const int32 Index)
{
	if (!InvenDatas.IsValidIndex(Index)) return;
	if (!InvenDatas[Index].IsEmpty) return;

	InvenDatas[Index].ItemData = FItemData();
	InvenDatas[Index].IsEmpty = true;

	OnItemUpdated.Broadcast(Index, InvenDatas[Index]);
}

