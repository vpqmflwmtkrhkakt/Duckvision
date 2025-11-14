// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "DebugHelper.h"
#include "UISubsystem.h"

void UInventoryComponent::AddItem(FItemData& ItemData)
{
	for (int32 i = 0; i < ItemDatas.Num(); ++i)
	{
		if (ItemDatas[i].ItemID == ItemData.ItemID)
		{
			if (ItemDatas[i].CurrentCount < ItemDatas[i].MaxCountPerSlot)
			{
				const int32 AddableCount = ItemDatas[i].MaxCountPerSlot - ItemDatas[i].CurrentCount;

				const int32 AddCount = FMath::Min(ItemData.CurrentCount, AddableCount);

				ItemDatas[i].CurrentCount += AddCount;

				ItemData.CurrentCount -= AddCount;

				OnItemAdded.Broadcast(i, ItemDatas[i]);
				if (ItemData.CurrentCount <= 0) break;
			}
		}
	}

	while (ItemData.CurrentCount > 0)
	{
		const int32 AddCount = FMath::Min(ItemData.CurrentCount, ItemData.MaxCountPerSlot);

		FInvenSlotData SlotData(ItemData.ItemID, ItemData.InvenIcon, AddCount, ItemData.MaxCountPerSlot, ItemData.bIsStackable);

		ItemDatas.Add(SlotData);

		OnItemAdded.Broadcast(ItemDatas.Num() - 1, SlotData);
		ItemData.CurrentCount -= AddCount;
	}
}
