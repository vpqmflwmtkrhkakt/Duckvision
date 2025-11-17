// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvenSlotData.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnItemAdded,
	int32, SlotIndex,
	FInvenSlotData, SlotData
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUCKVISION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemAdded OnItemAdded;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FItemData ItemData);
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", meta = (AllowPriateAccess = "true"))
	TArray<FInvenSlotData> ItemDatas;
};
