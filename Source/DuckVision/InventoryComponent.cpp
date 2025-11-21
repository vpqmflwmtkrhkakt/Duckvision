// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "DebugHelper.h"
#include "UISubsystem.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InvenDatas.SetNum(InventorySize);

	for (int32 i = 0; i < InvenDatas.Num(); ++i)
	{
		InvenDatas[i].SlotIndex = i;
		InvenDatas[i].IsEmpty = true;
		InvenDatas[i].ItemData = FItemData();
	}
}

FItemData UInventoryComponent::AddItem(FItemData ItemData)
{
	for (int32 i = 0; i < InvenDatas.Num(); ++i)
	{
		if (InvenDatas[i].IsEmpty) continue;

		if (InvenDatas[i].ItemData.ItemID == ItemData.ItemID)
		{
			if (InvenDatas[i].ItemData.CurrentCount < InvenDatas[i].ItemData.MaxCountPerSlot)
			{
				const int32 AddableCount = InvenDatas[i].ItemData.MaxCountPerSlot - InvenDatas[i].ItemData.CurrentCount;

				const int32 AddCount = FMath::Min(ItemData.CurrentCount, AddableCount);

				InvenDatas[i].ItemData.CurrentCount += AddCount;

				ItemData.CurrentCount -= AddCount;

				OnItemUpdated.Broadcast(InvenDatas[i].SlotIndex, InvenDatas[i]);

				if (ItemData.CurrentCount <= 0) return FItemData();
			}
		}
	}

	for (int32 i = 0; i < InvenDatas.Num() && ItemData.CurrentCount > 0; ++i)
	{
		if (!InvenDatas[i].IsEmpty) continue;

		const int32 AddCount = FMath::Min(ItemData.CurrentCount, ItemData.MaxCountPerSlot);

		FItemData InputItemData(ItemData.ItemID, ItemData.InvenIcon, AddCount, ItemData.MaxCountPerSlot, ItemData.bIsStackable);

		InvenDatas[i].ItemData = InputItemData;
		InvenDatas[i].IsEmpty = false;

		OnItemUpdated.Broadcast(InvenDatas[i].SlotIndex, InvenDatas[i]);

		ItemData.CurrentCount -= AddCount;
		if (ItemData.CurrentCount <= 0) return FItemData();
	}

	return ItemData;
}

void UInventoryComponent::UpdateInvenData(const int32 Index, FItemData ItemData)
{
	if (!InvenDatas.IsValidIndex(Index)) return;

	DebugHelper::Print("Index : " + FString::FromInt(Index));

	if (ItemData.CurrentCount <= 0)
	{
		InvenDatas[Index].IsEmpty = true;
		InvenDatas[Index].ItemData = FItemData();
	}
	else
	{
		InvenDatas[Index].IsEmpty = false;
		InvenDatas[Index].ItemData = ItemData;
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


