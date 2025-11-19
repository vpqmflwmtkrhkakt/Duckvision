// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvenSlotData.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnSlotItemUpdated,
	int32, SlotIndex,
	FInvenSlotData, SlotData
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUCKVISION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSlotItemUpdated OnItemUpdated;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemData AddItem(FItemData ItemData);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetInventorySize() const { return InventorySize;}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateItemData(const int32 Index, FItemData& ItemData);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(const int32 Index);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", meta = (AllowPriateAccess = "true"))
	TArray<FInvenSlotData> InvenDatas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 30;
};
